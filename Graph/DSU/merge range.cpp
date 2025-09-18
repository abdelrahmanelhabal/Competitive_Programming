struct DSU {
    vector<int> parent , group , next;
    int comp  , mx ;
    void init(int n) {
        comp = n ;
        mx = 1 ;
        parent.resize(n+1);
        group.resize(n+1);
        next.resize(n+2);
        for (int i = 0 ; i<=n;i++) { parent[i] = i; group[i] = 1 , next[i] = i;}
        next[n+1]=n+1;
    }

    int findNext(int x) {
        int cur = x;
        while (next[cur] != cur) cur = next[cur];
        int root = cur;
        cur = x;
        while (next[cur] != root) {
            int tmp = next[cur];
            next[cur] = root;
            cur = tmp;
        }
        return root;
    }

    int find(int node) {
        if (parent[node] == node) return node;
        return parent[node] = find(parent[node]);
    }

    bool merge(int u , int v) {
        int leaderU = find(u);
        int leaderV = find(v);
        if (leaderU == leaderV) {return false;}
        if (group[leaderU] > group[leaderV]) {swap(leaderU, leaderV);}
        parent[leaderU] = leaderV;
        group[leaderV] += group[leaderU];
        mx = max(mx,group[leaderV]);
        comp--;
        return true;
    }
    void mergeRange(int l, int r) {
        if (l > r) swap(l, r);
        int i = findNext(l);
        while (i < r) {
            merge(i, i + 1);
            next[i] = findNext(i + 1);
            i = next[i];
        }
    }
    int get_size(int node) { return group[find(node)]; }
    int get_max_size() {return mx;}
    bool sameGroup(int u , int v){return find(u)==find(v);}
};

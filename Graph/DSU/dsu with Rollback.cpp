struct RollBack {
    vector<int> parent , group ;
    stack<tuple<int,int,int>> back;
    int comp  , mx;
    void init(int n) {
        comp = n ;
        mx = 1 ;
        parent.resize(n+1);
        group.resize(n+1);
        for (int i = 0 ; i<=n;i++) { parent[i] = i; group[i] = 1;}
    }

    int find(int node) {
        if (parent[node] == node) return node;
        return find(parent[node]);
    }

    bool merge(int u , int v) {
        int leaderU = find(u);
        int leaderV = find(v);
        if (leaderU == leaderV) {
            back.emplace(-1,-1,-1);
            return false;
        }
        if (group[leaderU] > group[leaderV]) {swap(leaderU, leaderV);}
        back.emplace(leaderU,leaderV,mx);
        parent[leaderU] = leaderV;
        group[leaderV] += group[leaderU];
        mx = max(mx,group[leaderV]);
        comp--;
        return true;
    }
    void rollBack(int step) {
        while (step--) {
            if (back.empty()) return;
            auto [leaderU,leaderV,prev_mx] = back.top(); back.pop();
            if (leaderU == -1)continue;
            parent[leaderU] = leaderU;
            group[leaderV] -= group[leaderU];
            mx = prev_mx ;
            comp++;
        }
    }
    int get_size(int node) { return group[find(node)]; }
    int get_max_size() {return mx;}
    bool sameGroup(int u , int v){return find(u)==find(v);}
};

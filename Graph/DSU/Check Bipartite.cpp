struct RollBack {
    vector<int> parent , group , parity;
    stack<tuple<int,int,int,int>> back;
    bool bipartite = true;
    int comp  , mx;
 
    void init(int n) {
        comp = n ;
        mx = 1 ;
        parent.resize(n+1);
        parity.resize(n+1);
        group.resize(n+1);
        for (int i = 0 ; i<=n;i++) {
            parity[i] = 0 ;
            parent[i] = i;
            group[i] = 1;
        }
    }
 
    pair<int,int> find(int node) {
        int p = 0 ;
        while (node != parent[node]) {
            p ^= parity[node];
            node = parent[node] ;
        }
        return {node,p};
    }
 
    bool merge(int u , int v) {
        auto a = find(u);
        auto b = find(v);
 
        int ru = a.first ;
        int rv = b.first ;
 
        int pu = a.second ;
        int pv = b.second;
 
        if (ru == rv) {
            back.emplace(-1,-1,-1,bipartite);
            if (pu == pv) bipartite = false;
            return false;
        }
 
        if (group[ru] < group[rv]) {
            swap(ru, rv);
            swap(pu,pv);
        }
 
        back.emplace(ru,rv,group[ru],bipartite);
 
        parent[rv] = ru;
        parity[rv] = pu ^ pv ^ 1 ;
        group[ru] += group[rv];
        comp--;
 
        return true;
    }
 
    void rollBack(int step) {
        while (step--) {
            auto [ru,rv,old_size,old_bip] = back.top();
            back.pop();
 
            bipartite = old_bip;
 
            if (ru == -1) continue;
 
            parent[rv] = rv;
            group[ru] = old_size;
            parity[rv] = 0;
            comp++;
        }
    }
 
    int get_size(int node) { return group[find(node).first]; }
    int get_max_size() {return mx;}
    bool sameGroup(int u , int v){return find(u).first==find(v).first;}
};

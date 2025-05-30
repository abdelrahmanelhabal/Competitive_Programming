struct UnDirectEulerCycle {
    vector<multiset<int>>adj;
    vector<int> deg , tour;
    int n , m ;
    UnDirectEulerCycle(int n , vector<pair<int,int>>&edge) {
        this-> n = n ;
        m = edge.size();
        deg.resize(n,0);
        adj.resize(n);
        for (auto &[u,v]:edge) {
            adj[u].emplace(v);
            adj[v].emplace(u);
            deg[u]++;
            deg[v]++;
        }
    }
    void dfs(int node) {
        while (!adj[node].empty()) {
            int child = *adj[node].begin();
            adj[node].erase(adj[node].begin());
            adj[child].erase(adj[child].find(node));
            dfs(child);
        }
        tour.emplace_back(node);
    }

    bool get() {
        for (int i = 0; i < n; ++i) {
            if (deg[i] % 2 != 0) {
                return false;
            }
        }
        dfs(0);
        reverse(all(tour));
        if (tour.size() != m+1) {
            return false;
        }
        return true;
    }
};
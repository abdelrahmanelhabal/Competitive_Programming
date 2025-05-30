struct DirectEulerPath {
    vector<vector<int>>adj;
    vector<int> in , out , tour;
    int n , s , e , m ;
    DirectEulerPath(int n , int start , int end , vector<pair<int,int>>&edge) {
        this-> n = n ;
        s = start , e = end ;
        m = edge.size();
        adj.resize(n);in.resize(n);out.resize(n);
        for (auto &[u,v]:edge) {
            adj[u].emplace_back(v);
            out[u]++;
            in[v]++;
        }
    }
    bool get() {
        for (int i = 0; i < n; ++i) {
            if (i == s) {
                if (out[i] != in[i] + 1) return false ;
            } else if (i == e) {
                if (in[i] != out[i] + 1) return false ;
            } else {
                if (in[i] != out[i]) return false ;
            }
        }
        dfs(s);
        reverse(all(tour));
        if ((int)tour.size() != m + 1 || tour.front() != s || tour.back() != e) {
           return false;
        }
        return true;
    }
    void dfs(int node) {
        while (out[node]) {
            out[node]--;
            int child = adj[node][out[node]];
            dfs(child);
        }
        tour.emplace_back(node);
    }
};
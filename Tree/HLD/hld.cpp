struct HLD {
    vector<int>big,sz,par,head,in,dep,node,out;
    int timer ;
 
    void dfs(int v , vector<vector<int>>&adj) {
        for (auto u  : adj[v]) {
            if (u == par[v])continue;
            par[u] = v ;
            dep[u] = dep[v] + 1 ;
            dfs(u,adj);
            sz[v] += sz[u];
            if (big[v] == 0 || sz[u] > sz[big[v]]) big[v] = u ;
        }
    }
 
    void flatten(int v , vector<vector<int>>&adj) {
        node[timer] = v ;
        in[v] = timer++;
        if (big[v]) {
            head[big[v]] = head[v];
            flatten(big[v],adj);
        }
        for (auto u  : adj[v]) {
            if (u == par[v] || u == big[v])continue;
            head[u] = u ;
            flatten(u , adj);
        }
        out[v] = timer ; 
    }
 
    HLD(int n , vector<vector<int>>&adj) {
        big.assign(n + 1 , 0) ; sz.assign(n + 1 , 1) ;
        par.assign(n + 1 , 0 ) ; head.assign(n + 1 , 1) ;
        dep.assign(n + 1 , 0 ); out.assign(n + 1, 0);
        node.assign(n + 1 , 9); in.assign(n + 1, 0);
 
        dfs(1,adj);
        timer = 0 ;
        head[1] = 1 ;
        flatten(1,adj);
    }
 
    vector<pair<int,int>> getPath(int u , int v) {
        vector<pair<int,int>>res;
        while (true) {
            if (head[u] == head[v]) {
                if (dep[u] > dep[v]) swap(u,v);
                // u is lca
                res.emplace_back(in[u], in[v]);
                return res;
            }
 
            if (dep[head[u]] > dep[head[v]]) swap(u,v);
            res.emplace_back(in[head[v]],in[v]);
            v = par[head[v]];
        }
    }
};

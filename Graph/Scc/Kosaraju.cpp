vector<int>comp , vis , id , roots;
vector<vector<int>>scc , dag;
void dfs(int node , vector<vector<int>>&adj) {
    vis[node] = 1 ;
    for (auto child : adj[node]) {
        if (vis[child]) continue;
        dfs(child,adj);
    }
    comp.emplace_back(node);
}
void Kosaraju(int  n , vector<vector<int>>&adj,vector<vector<int>>&rAdj) {
    comp.clear();
    vis.assign(n, 0);
    id.assign(n, -1);
    roots.clear();
    scc.clear();
    dag.clear();
    dag.resize(n);
    for (int i = 0 ; i < n ; i++) {
        if (!vis[i])dfs(i,adj);
    }
    auto order = comp ;
    reverse(all(order));
    vis.assign(n, 0);
    for (auto node : order) {
        if (vis[node])continue;
        comp.clear();
        dfs(node,rAdj);
        scc.emplace_back(comp);
        for (auto child : comp) {
            id[child] = comp.front();
        }
        roots.emplace_back(comp.front());
    }

    for (int u = 0 ; u < n ; u++) {
        for (auto v : adj[u]) {
            if (id[u]!=id[v]) {
                dag[id[u]].emplace_back(id[v]);
            }
        }
    }
}
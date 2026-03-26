vector<int> comp, vis, ids, roots, val, inDeg, outDeg, compSz;
vector<vector<int>> scc, dag;
int id ;
void dfs(int u , vector<vector<int>>& adj) {
    vis[u] = 1;
    for (auto v : adj[u]) {
        if (vis[v]) continue;
        dfs(v, adj);
    }
    comp.emplace_back(u);
}
void init(int n) {
    comp.clear();
    vis.assign(n, 0);
    ids.assign(n, -1);
    roots.clear();
    scc.clear();
    dag.clear();
    dag.resize(n);
    inDeg.assign(n, 0);
    outDeg.assign(n, 0);
    compSz.assign(n, 0);
    id = -1 ;
}
void Kosaraju(int n, vector<vector<int>>& adj, vector<vector<int>>& rAdj) {
    init(n);

    for (int i = 0; i < n; i++) {
        if (!vis[i]) dfs(i, adj);
    }

    auto order = comp;

    reverse(all(order));

    vis.assign(n, 0);
    for (auto u : order) {
        if (vis[u]) continue;
        comp.clear();
        dfs(u, rAdj);
        id++;
        scc.emplace_back(comp);
        compSz[id] = comp.size();
        for (auto v : comp) {
            ids[v] = id;
        }
        roots.emplace_back(id);
    }

    for (int u = 0; u < n; u++) {
        for (auto v : adj[u]) {
            if (ids[u] != ids[v]) {
                dag[ids[u]].emplace_back(ids[v]);
                inDeg[ids[v]]++;
                outDeg[ids[u]]++;
            }
        }
    }
}


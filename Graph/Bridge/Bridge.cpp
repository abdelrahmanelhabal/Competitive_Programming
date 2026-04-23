int const N = 2e5+5;
int n ;
vector<int> vis, low , depth ;
vector<int>adj[N];
vector<pair<int,int>>bridge;
void dfs(int u , int par) {
    vis[u] = 1 ;
    low[u] = depth[u];
    for (auto v : adj[u]) {
        if (v == par)continue;
        if (vis[v]) { // back-edge
            low[u] = min(low[u],depth[v]);
            continue;
        }
        depth[v] = depth[u] + 1;
        dfs(v,u);
        low[u] = min(low[u],low[v]);

        if (low[v] > depth[u]) {
            bridge.emplace_back(u, v);
        }
    }
}
void Bridge() {
    low.assign(n,1e9);
    depth.assign(n,0);
    vis.assign(n,0);
    for (int i = 0 ; i < n ; i++) {
        if (!vis[i]) {
            dfs(i,-1);
        }
    }
}

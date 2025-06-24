int n ;
vector<int> vis, low , depth ;
vector<vector<int>>adj;
vector<pair<int,int>>bridge;
void dfs(int node , int parent) {
    vis[node] = 1 ;
    low[node] = depth[node];
    for (auto child : adj[node]) {
        if (child == parent)continue;
        if (vis[child]) { // back-edge
            low[node] = min(low[node],depth[child]);
            continue;
        }
        depth[child] = depth[node] + 1;
        dfs(child,node);
        low[node] = min(low[node],low[child]);

        if (low[child] > depth[node]) {
            bridge.emplace_back(node, child);
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
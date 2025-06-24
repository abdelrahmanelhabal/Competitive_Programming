int n ;
vector<int> vis, low , depth , is_art_point;
vector<vector<int>>adj;
void dfs(int node , int parent) {
    vis[node] = 1 ;
    low[node] = depth[node];
    int kids = 0 ;
    for (auto child : adj[node]) {
        if (child == parent)continue;
        if (vis[child]) { // back-edge
            low[node] = min(low[node],depth[child]);
            continue;
        }
        kids++ ;
        depth[child] = depth[node] + 1;
        dfs(child,node);
        low[node] = min(low[node],low[child]);

        if (~parent && low[child] >= depth[node] ) {
            is_art_point[node] = 1 ;
        }
    }
    if (parent == -1 && kids > 1) {
        is_art_point[node] = 1;
    }
}
void Art() {
    low.assign(n,1e9);
    depth.assign(n,0);
    vis.assign(n,0);
    is_art_point.assign(n,0);
    for (int i = 0 ; i < n ; i++) {
        if (!vis[i]) {
            dfs(i,-1);
        }
    }
}
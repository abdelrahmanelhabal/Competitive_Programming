int n , m  , cur_id = 0   ;
vector<int> vis, low , depth , is_bridge , id , siz ;
vector<vector<pair<int,int>>>adj;
vector<vector<int>>tree;
void dfs(int node , int parent) {
    vis[node] = 1 ;
    low[node] = depth[node];
    for (auto [child , idx]  : adj[node]) {
        if (child == parent)continue;
        if (vis[child]) { // back-edge
            low[node] = min(low[node],depth[child]);
            continue;
        }
        depth[child] = depth[node] + 1;
        dfs(child,node);
        low[node] = min(low[node],low[child]);

        if (low[child] > depth[node]) {
            is_bridge[idx] = 1;
        }
    }
}
void dfs_tree(int node) {
    id[node] = cur_id ;
    siz[cur_id]++;
    for (auto [child , idx] : adj[node]) {
        if (id[child] != -1 || is_bridge[idx]) {continue;}
        dfs_tree(child);
    }
}
void get_bridge_tree() {
    cur_id = 0 ;
    low.assign(n,1e9);
    depth.assign(n,0);
    vis.assign(n,0);
    is_bridge.assign(m,0);
    siz.assign(n,0);
    id.assign(n,-1);
    tree.assign(n,vector<int>());

    dfs(0,-1); 

    for (int i = 0 ; i < n ; i++) {
        if (id[i]==-1) {
            dfs_tree(i);
            cur_id++;
        }
    }
    for (int u = 0 ; u < n ; u++) {
        for (auto [v,idx] : adj[u]) {
            if (id[u]!=id[v]) {
                tree[id[v]].emplace_back(id[u]);
                tree[id[u]].emplace_back(id[v]);
            }
        }
    }
}

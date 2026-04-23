int const N = 2e5 + 5 ; 
int n , m  , cur_id = 0   ;
vector<int> vis, low , depth , is_bridge , id , siz ;
vector<pair<int,int>>adj[N];
vector<vector<int>>tree;
void dfs(int u , int par) {
    vis[u] = 1 ;
    low[u] = depth[u];
    for (auto [v , idx]  : adj[u]) {
        if (v == par)continue;
        if (vis[v]) { // back-edge
            low[u] = min(low[u],depth[v]);
            continue;
        }
        depth[v] = depth[u] + 1;
        dfs(v,u);
        low[u] = min(low[u],low[v]);
 
        if (low[v] > depth[u]) {
            is_bridge[idx] = 1;
        }
    }
}
void dfs_tree(int u) {
    id[u] = cur_id ;
    siz[cur_id]++;
    for (auto [v , idx] : adj[u]) {
        if (id[v] != -1 || is_bridge[idx]) {continue;}
        dfs_tree(v);
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
            }
        }
    }
}

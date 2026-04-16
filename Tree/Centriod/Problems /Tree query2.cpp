int depth[N];
vector<int>adj[N] , centroid_tree[N];
int centroid_parent[N];
int n , m , sz[N] , centroid_tree_root = -1;
bool removed[N];
int dfs_sz(int u, int p) {
    sz[u] = 1;
    for (auto &v : adj[u]) {
        if (v == p || removed[v])continue;
        sz[u] += dfs_sz(v , u);
    }
    return sz[u];
}
 
int dfs_centroid(int u, int p, int s) {
    for (auto &v : adj[u]) {
        if (v == p || removed[v]) continue;
        if (sz[v] * 2 > s) return dfs_centroid(v , u , s);
    }
    return u;
}
map<int , int> dist[N];
void dfs_dist(int u, int p, int c, int d) {
    dist[c][u] = d;
    for (int v : adj[u]) {
        if (v == p || removed[v]) continue;
        dfs_dist(v, u, c, d + 1);
    }
}
 
int decompose(int u) {
    int comp_sz   = dfs_sz(u, -1);
    int centroid  = dfs_centroid(u, -1, comp_sz);
    if (centroid_tree_root == -1) centroid_tree_root = centroid;
    removed[centroid] = true;
 
    dist[centroid][centroid] = 0;
 
    for (int v : adj[centroid]) {
        if (!removed[v]) {
            dfs_dist(v, centroid, centroid, 1);
        }
    }
    for (auto &v : adj[centroid]) {
        if (!removed[v]) {
            int x = decompose(v);
            centroid_tree[centroid].emplace_back(x);
            centroid_tree[x].emplace_back(centroid);
            centroid_parent[x] = centroid;
        }
    }
    return centroid;
}
void solve(){
    int q ; cin >> n >> q ; 
    for(int i = 1 ; i < n ; i++){
        int u , v ; cin >> u >> v ; 
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    memset(centroid_parent , -1 , sizeof(centroid_parent));
    int root = decompose(0);
    vector<int>val(n , 1e18);
    auto update = [&](int u){
        val[u] = 0 ; 
        int c = u ; 
        while(centroid_parent[u] != -1){
            u = centroid_parent[u] ; 
            val[u] = min(val[u] , dist[u][c]);
        }
    };
    auto qry = [&](int u){
        int res = val[u];
        int c = u ; 
        while(centroid_parent[u] != -1){
            u = centroid_parent[u] ; 
            res = min(res , val[u] + dist[u][c]);
        }
        return res ; 
    };
    update(0);
    while(q--){
        int type , u ; cin >> type >> u ; 
        u--;
        if(type == 1){
            update(u);
        }
        else{
            cout << qry(u) << endl ;
        }
    }
}

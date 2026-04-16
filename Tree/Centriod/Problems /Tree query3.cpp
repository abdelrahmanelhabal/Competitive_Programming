const int N = 2e5 + 10 , K = 19;
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
vector<pair<int,int>> dist[N];
void dfs_dist(int u, int p, int c, int d) {
    dist[u].emplace_back(c , d); 
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
 
    dist[centroid].emplace_back(centroid , 0);
 
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
    cin >> n ;  
    for(int i = 1 ; i < n ; i++){
        int u , v ; cin >> u >> v ; 
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    memset(centroid_parent , -1 , sizeof(centroid_parent));
    int root = decompose(0);

    vector<multiset<int>> val(n) ; 
    auto update = [&](int u , int type){
        if(type == 1){ // from black to  white 
            for(auto [v , d] : dist[u] ){
                val[v].insert(d);
            }
        }
        else{ // from white to black 
            for(auto [v , d] : dist[u]){
                 val[v].erase(val[v].find(d));
            }
        }
    };
    int const INF = 1e18 ; 
    auto qry = [&](int u){
        int res = INF ;  
        for(auto [v , d] : dist[u]){
            if(val[v].size())
                res = min(res , *val[v].begin() + d);     
        }
        if(res == 1e18) return -1ll;
        return res ; 
    };
    
}

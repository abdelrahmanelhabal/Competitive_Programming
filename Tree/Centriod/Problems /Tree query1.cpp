const int N = 2e5 + 10;
 
vector<pair<int,int>> adj[N], dist[N];
vector<int> allDist[N];
map<int, vector<int>> distSub[N];
map<int,int> childOf[N]; 
 
int n, q, sz[N];
bool removed[N];
 
int dfs_sz(int u, int p) {
    sz[u] = 1;
    for (auto [v , w] : adj[u]) {
        if (v == p || removed[v]) continue;
        sz[u] += dfs_sz(v , u);
    }
    return sz[u] ;
}
 
int dfs_centroid(int u, int p, int s) {
    for (auto [v , w] : adj[u]) {
        if (v == p || removed[v]) continue;
        if (sz[v] * 2 > s) return dfs_centroid(v , u , s);
    }
    return u ;
}
 
void dfs_dist(int u, int p, int c, int d , int rootChild) {
    dist[u].emplace_back(c , d);
    allDist[c].emplace_back(d); 
    distSub[c][rootChild].emplace_back(d);
    childOf[u][c] = rootChild; 
 
    for (auto [v , w] : adj[u]) {
        if (v == p || removed[v]) continue;
        dfs_dist(v, u, c, d + w , rootChild);
    }
}
 
void decompose(int u) {
    int comp_sz = dfs_sz(u, -1);
    int centroid = dfs_centroid(u, -1, comp_sz);
    removed[centroid] = true;
 
    dist[centroid].emplace_back(centroid , 0);
    allDist[centroid].emplace_back(0);
    childOf[centroid][centroid] = -1; 
 
    for (auto [v , w] : adj[centroid]) {
        if (!removed[v]) {
            dfs_dist(v, centroid, centroid, w , v);
        }
    }
 
    sort(all(allDist[centroid]));
    for (auto &it : distSub[centroid]) {
        sort(all(it.second));
    }
 
    for (auto [v , w] : adj[centroid]) {
        if (!removed[v]) {
            decompose(v);
        }
    }
}
 
int query(int v, int l) {
    int ans = 0;
 
    for (auto [c, d] : dist[v]) {
        if (d > l) continue;
 
        int need = l - d;
 
        int cnt = upper_bound(all(allDist[c]), need) - allDist[c].begin();
 
        int u = childOf[v][c]; 
 
        if (u != -1) {
            int sub = upper_bound(all(distSub[c][u]), need) - distSub[c][u].begin();
            cnt -= sub;
        }
 
        ans += cnt;
    }
 
    return ans;
}
void solve(){
    cin >> n >> q ; 
    for(int i = 1 ; i< n ; i++){
        int u , v , w ; cin >> u >> v >> w ;
        u--,v--; 
        adj[u].emplace_back(v , w);
        adj[v].emplace_back(u , w);
    }
    decompose(0);
    while(q--){
        int u , l ; cin >> u >> l ; 
        u--;
        cout << query(u , l) << endl ;
    }
 
}


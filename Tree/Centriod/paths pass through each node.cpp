const int N = 2e5 + 10;
vector<int>adj[N];
int n , sz[N] , ans[N], res = 0;
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

void dfs_add(int u , int p  , int delta , int depth = 1) {
    for (auto &v : adj[u]) {
        if (removed[v] || v == p) continue;
        dfs_add(v , u ,   delta , depth + 1 );
    }
}

void dfs_ans(int u , int p , int centroid , int depth = 1 ) {
    for (auto &v : adj[u]) {
        if (removed[v] || v == p) continue;
        dfs_ans(v , u , centroid, depth + 1);
    }
}

int dfs_contrubition(int u , int p , int centroid , int depth = 1) {
    int ret = 0;
    for (auto &v : adj[u]) {
        if (removed[v] || v == p) continue;
        ret += dfs_contrubition(v , u , centroid, depth + 1);
    }
    ans[u] += ret;
    return ret;
}

void decompose(int u) {
    int comp_sz   = dfs_sz(u, -1);
    int centroid  = dfs_centroid(u, -1, comp_sz);

    for (auto &v : adj[centroid]) {
        if (removed[v]) continue;
        dfs_ans(v, centroid , centroid);
        dfs_add(v, centroid , +1);
    }

    
    for (auto &v : adj[centroid]) {
        if (removed[v]) continue;
        dfs_add(v , centroid , -1);
        dfs_contrubition(v , centroid , centroid);
        dfs_add(v , centroid , +1);
    }
  
    for (auto &v : adj[centroid]) {
        if (removed[v]) continue;
        dfs_add(v, centroid , -1);
    }
   
   
    removed[centroid] = true;
    for (auto &v : adj[centroid]) {
        if (!removed[v]) {
            decompose(v);
        }
    }
}


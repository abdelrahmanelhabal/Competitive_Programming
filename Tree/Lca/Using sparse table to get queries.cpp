int const Log = 40 , N = 1e5+5;
int n , q  , root = 1 , parent[N] ,up[N][Log] , sp[N][Log] , depth[N];
vector<pair<int,int>>adj[N] ;
void dfs(int node , int parent) {
    for (auto [child,w] : adj[node]) {
        if (child == parent) {continue;}
        depth[child] = depth[node]+1;
        up[child][0] = node;
        sp[child][0] = w  ;
        for (int i = 1 ; i < Log ; i++) {
            up[child][i] = up[up[child][i-1]][i-1];
            sp[child][i] = max(sp[child][i-1] , sp[up[child][i-1]][i-1]);
        }
        dfs(child,node);
    }
}
void build() {
    depth[root] = 0;
    dfs(root,-1);
}
int kth_ancestor(int node , int k) {
    for (int i = 0 ; i < Log ; i++) {
        if (k >> i & 1) {
            node = up[node][i];
        }
    }
    return node;
}
int lca(int u , int v) {
    if (depth[u] < depth[v]) {swap(u,v);}
    int k = depth[u] - depth[v];
    u = kth_ancestor(u,k);

    if (u == v) { return v; }

    for (int i = Log -1 ; i >= 0 ;i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[v][0];
}
int get_max(int node , int k) {
    if (depth[node] < k ) return -1e18;
    int ret = -1e18 ;
    for (int j = 0  ; j < Log ; j++) {
        if (k >> j & 1) {
            ret = max(ret,sp[node][j]);
            node = up[node][j];
        }
    }
    return ret;
}
int query(int u ,  int v) {
    int l = lca(u,v);
    return max(get_max(u , depth[u]-depth[l]),get_max(v,depth[v]-depth[l]));
}


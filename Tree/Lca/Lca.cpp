int const Log = 40 , N = 3e5+5;
int n , q , root = 1 , parent[N] ,up[N][Log] , depth[N];
vector<int>adj[N] ;
void dfs(int node , int parent) {
    depth[node] = depth[parent]+1;
    up[node][0] = parent;
    for (int i = 1 ; i < Log ; i++) {
        up[node][i] = up[up[node][i-1]][i-1];
    }
    for (auto child : adj[node]) {
        if (child == parent) {continue;}
        dfs(child,node);
    }
}
void build() {
    depth[root] = 1;
    dfs(root,0);
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
int dis(int u , int v) {
    int l = lca(u,v);
    return depth[u] + depth[v] - 2 * depth[l];
}

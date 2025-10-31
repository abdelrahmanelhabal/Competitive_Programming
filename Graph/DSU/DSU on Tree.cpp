int const N = 1e5+4;
vector<int>adj[N];
int  depth[N] ,sz[N] , ans[N] , big[N];
vector<pair<int,int>>queries[N];
void dfs(int u , int p) {
    sz[u]=1;
    big[u]=-1;
    depth[u] = (p == -1 ? 0 : depth[p] + 1);
    for (auto v : adj[u]) {
        if (v == p) continue;
        dfs(v , u);
        sz[u]+=sz[v];
        if (big[u] == -1 || sz[v] > sz[big[u]] )
            big[u] = v;
    }
}
void update(int u , int d) {

}
void add(int u , int p ,int d) {
    update(u,d);
    for (auto v : adj[u]) {
        if (v == p)continue;
        add(v,u,d);
    }
}
void sack(int u , int p , int keep) {
    for (auto v : adj[u]) {
        if (v == p || v == big[u])continue;
        sack(v,u , 0);
    }
    // add to DS
    if (big[u]!=-1)
        sack(big[u],u,1);
    update(u,1);
    for (auto v : adj[u]) {
        if (v == p || v == big[u])continue;
        add(v,u , 1); // light / small subtree
    }
    // answer queries

    // remove from DS
    if (!keep) {
        add(u,p,-1);
    }
}


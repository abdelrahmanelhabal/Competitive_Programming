int const N = 1e5+1, Log = 20 , block_size = 440 ;
int n , q , in[N] , out[N], nodes[2 * N] , Timer = 0 , up[Log][N] , depth[N]   , parity[N];
vector<int> adj[N] ;
void dfs(int u , int p) {
    in[u] = Timer ;
    nodes[Timer] = u ;
    Timer++;
    up[0][u] = p ;
    depth[u] = depth[p]+1 ;
    for (auto v : adj[u]) {
        if (v == p)continue;
        dfs(v,u);
    }
    out[u] = Timer ;
    nodes[Timer] = u ;
    Timer++;
}
void build() {
    for (int i = 1 ; i< Log ; i++) {
        for (int j = 0 ; j < n ; j++) {
            up[i][j] = up[i - 1][up[i - 1][j]];
        }
    }
}
int walk(int u , int k) {
    for (int i = 0 ; i < Log ; i++) {
        if (k >> i & 1) {
            u = up[i][u];
        }
    }
    return u ;
}
int lca(int u ,int v) {
      if (depth[u] > depth[v]) {swap(u,v); }
    v = walk(v,depth[v] - depth[u]);
    if (u == v)return u ;
    for (int i = Log-1 ; i >= 0 ; i--) {
        if (up[i][u] != up[i][v]) {
            u = up[i][u];
            v = up[i][v];
        }
    }
    return up[0][u];
}
struct Query {
    int l , r  , idx , lca , need ;
    Query(int l , int r , int idx ,int lca , int need) : l(l) , r(r) , idx(idx),lca(lca),need(need){}
    bool operator<(const Query& other) const {
        int bla = l / block_size ;
        int blb = other.l / block_size ;
        if (bla != blb) { return bla < blb;}
        return (bla & 1 ^ 1) ? r < other.r : r > other.r ;
    }
};
void add(int u) {

}
void erase(int u) {

}
void update(int MoIdx) {
    if (parity[nodes[MoIdx]] & 1)  {
        erase(nodes[MoIdx]);
    }
    else {
        add(nodes[MoIdx]);
    }
    parity[nodes[MoIdx]]^=1;
}
void Mo(vector<Query> &queries) {
    int MoLeft = 0,MoRight = -1;
    for(auto &q: queries) {
        while(MoRight < q.r) update(++MoRight);
        while(MoLeft > q.l) update(--MoLeft);
        while(MoRight > q.r) update(MoRight--);
        while(MoLeft < q.l) update(MoLeft++);
        if (q.need) {
            add(q.lca);
        }
        //ans[q.idx] = res ;
        if (q.need) {
            erase(q.lca);
        }
    }
}
void solve() {
    cin >> n >> q ;
    for (int i = 1 ; i< n ; i++) {
        int u ,v ; cin >> u >> v ;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(0,0);
    build();
    vector<Query>queries;
    for (int i = 0 ; i < q ; i++) {
        int u , v ; cin >> u >> v ;
        u--,v--;
        if (in[u] > in[v]) swap(u,v);
        int l = lca(u,v);
        if (l == u) {
            queries.emplace_back(in[u],in[v],i,l,false);
        }
        else {
            queries.emplace_back(out[u],in[v],i,l,true);
        }
    }
    sort(all(queries));
    Mo(queries);
    // for (int i = 0 ; i < q ; i++) {
    //     cout << ans[i] << endl ;
    // }
}

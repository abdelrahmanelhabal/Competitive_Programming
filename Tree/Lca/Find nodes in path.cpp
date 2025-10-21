// probelm : https://codeforces.com/contest/587/problem/C
int const Log = 20 , N = 1e5+5;
int n , m ,  q  , root = 1 , up[N][Log]  , depth[N];
vector<int> best[N][Log] , c[N] , adj[N];
vector<int> merge(vector<int>&a,vector<int>&b , int limit) {
    vector<int>res;
    int i = 0 , j = 0 , cnt = 0 ;
    while (cnt < limit && i < a.size() && j < b.size()) {
        if (a[i] < b[j]) { res.emplace_back(a[i]); i++; cnt++; }
        else { res.emplace_back(b[j]); j++; cnt++; }
    }
    while (cnt < limit && i < a.size() ) {
        res.emplace_back(a[i]); i++;cnt++;
    }
    while (cnt < limit && j < b.size() ) {
        res.emplace_back(b[j]); j++; cnt++;
    }
    return res;
}
void dfs(int node , int parent) {
    depth[node] = depth[parent]+1;
    best[node][0] = c[node];
    up[node][0] = parent;
    for (int i = 1 ; i < Log ; i++) {
        up[node][i] = up[up[node][i-1]][i-1];
        best[node][i] = merge(best[node][i-1],best[up[node][i-1]][i-1],10);
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
vector<int> finds(int node , int k , int limit) {
    vector<int>res ;
    for (int i = 0 ; i< Log ; i++) {
        if (k >> i & 1) {
            res = merge(res,best[node][i],limit);
            node = up[node][i];
        }
    }
    return res;
}
vector<int>query(int u , int v ,int limit) {
    vector<int>res;
    int l = lca(u,v);
    vector<int>path1= finds(u,depth[u]-depth[l],limit);
    res =merge(res,path1,limit);
    vector<int>path2= finds(v,depth[v]-depth[l],limit);
    res =merge(res,path2,limit);
    res = merge(res,c[l],limit);
    return res;
}
void solve() {
    cin >> n >> m >> q ;
    for (int i = 1 ; i< n ; i++) {
        int u ,v  ; cin >> u >> v ;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    for (int i = 1 ; i <=m ; i++) {
        int x ; cin >> x ;
        if (c[x].size() < 10)
            c[x].emplace_back(i);
    }
    build();
    while (q--) {
        int u , v , a ; cin >> u >>v  >> a ;
        vector<int>res = query(u,v,a);
        cout << res.size() << " ";
        for (auto i : res) {
            cout << i << " " ;
        }
        cout << endl ;
    }
}

int const N = 2e5+4;
int  n , col[N] , ans[N] ;
vector<int>adj[N];
set<int>c[N];
void dfs(int  u ,int p) {
    c[u].insert(col[u]);
    for (auto v : adj[u]) {
        if (v == p)continue;
        dfs(v,u);
        if (c[u].size() < c[v].size()) {swap(c[u],c[v]);}
        for (auto i : c[v]) {
            c[u].insert(i);
        }
    }
    ans[u] = c[u].size();
}

#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'
int const Log = 40 , N = 5e5+5;
int n , q , root = 1 , parent[N] ,up[N][Log] , depth[N];
vector<int>adj[N] ;
void dfs(int node , int parent) {
    for (auto child : adj[node]) {
        if (child == parent) {continue;}
        depth[child] = depth[node]+1;
        up[child][0] = node;
        for (int i = 1 ; i < Log ; i++) {
            up[child][i] = up[up[child][i-1]][i-1];
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
int dis(int u , int v) {
    int l = lca(u,v);
    return depth[u] + depth[v] - 2 * depth[l];
}

void solve() {
cin >> n >> q ;
    for (int i = 1 ; i < n ; i++) {
        int u , v ; cin >> u >> v ;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    build();
    while (q--) {
        int u, v ; cin >> u >> v ;
        cout << dis(u,v) << endl ;
    }
}

signed main() {
    #ifndef ONLINE_JUDGE
         freopen("input.txt", "r", stdin);
       freopen("output.txt", "w", stdout);
     #endif
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int tc =1;  //cin >> tc ;
    while (tc--) solve();
    return 0;
}

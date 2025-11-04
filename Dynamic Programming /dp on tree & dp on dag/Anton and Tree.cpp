problem link : https://codeforces.com/contest/734/problem/E

#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'
int const N = 2e5+5;
vector<int>adj[N] , tree[N];
int n , color[N] , vis[N];
int id = 0;
void dfs(int node , int parent) {
    vis[node] = id ;
    for (auto child : adj[node]) {
        if (child == parent || color[child]!=color[node])continue;
        dfs(child,node);
    }
}
pair<int,int> bfs(int start) {
    queue<int> q;
    vector<int>dis(id,1e18);
    q.emplace(start);
    dis[start] = 0;
    while (!q.empty()) {
        auto node = q.front(); q.pop();
        for (auto child : tree[node]) {
            if (dis[child] == 1e18) {
                dis[child]=dis[node]+1;
                q.emplace(child);
            }
        }
    }
    int node = -1 , mx = -1 ;
    for (int i =0 ; i< id ; i++ ) {
        if (dis[i] > mx) {
            mx = dis[i];
            node = i ;
        }
    }
    return {node,mx};
}
void solve() {
    cin >> n ;
    for (int i = 0 ; i< n ; i++) {
        adj[i].clear();
        vis[i]=-1;
    }
    for (int i =0 ; i< n ; i++) { cin >> color[i]; }

    for (int i = 1; i < n ; ++i) {
        int u , v ; cin >> u >> v ;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for (int i = 0 ; i< n ; i++) {
        if (vis[i] == -1) {
            dfs(i,i);
            id++;
        }
    }

    for (int i = 0 ;i < id ; i++) { tree[i].clear(); }

    for (int node = 0 ; node < n ; node++) {
        for (auto child : adj[node]) {
            if (vis[child]!=vis[node]) {
                tree[vis[child]].emplace_back(vis[node]);
            }
        }
    }
    auto [x,mx1] = bfs(0);
    auto [y ,mx] = bfs(x);
    cout << (mx +1)/2 << endl ;
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int tc = 1; //cin >> tc ;
    while (tc--) solve();
    return 0;
}

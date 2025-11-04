problem link : https://codeforces.com/contest/2014/problem/F


#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'
int const N = 2e5+5;
int n , c , a[N] , dp[N][2];
vector<int>adj[N];
// dp[node][1] // safe node
//dp[node][0] // not safe node ;
void dfs(int node , int parent) {
    for (auto child : adj[node]) {
        if (child == parent)continue;
        dfs(child,node);
    }
    dp[node][1] = a[node];
    for (auto child : adj[node]) {
        if (child == parent){continue;}
        dp[node][0] += max(dp[child][0],dp[child][1]);
        dp[node][1] += max(dp[child][0],dp[child][1]-2*c);
    }
}
void solve() {
    cin >> n >> c ;
    for (int i = 0 ;i < n ; i++) {
        dp[i][0] = dp[i][1] = 0;
        adj[i].clear();
    }
    for (int i = 0 ; i < n ; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < n ; i++) {
        int u , v ; cin >> u >> v ;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(0,0);
    cout << max(dp[0][0],dp[0][1]) << endl ;

}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int tc = 1; cin >> tc ;
    while (tc--) solve();
    return 0;
}

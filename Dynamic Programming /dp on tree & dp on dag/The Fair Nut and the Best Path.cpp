problem link : https://codeforces.com/contest/1083/problem/A

#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'
int const N =3e5+5;
int n , val[N] , dp[N] , ans ;
vector<pair<int,int>>adj[N];
void dfs(int node , int parent) {
    dp[node] = val[node];
    for (auto [child , cost] : adj[node]) {
        if (child == parent) continue ;
        dfs(child, node);
        int rem = dp[child] - cost ;
        ans = max(ans,dp[node] + rem);
        dp[node] = max(dp[node],val[node]+rem);

    }
    ans = max(ans,dp[node]);
}
void solve() {
    cin >> n ;
    for (int i= 0 ;i < n ;i++) {
        cin >> val[i];
    }
    for (int i = 1 ; i< n ; i++) {
        int u , v , w; cin >> u >> v >> w ;
        u--,v--;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    dfs(0,0);
    cout << ans << endl ;
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

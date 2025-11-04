problem link : https://atcoder.jp/contests/dp/tasks/dp_p

#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'
int const N = 1e5+5;
int n , dp[N][2];
vector<int>adj[N];
int const mod = 1e9+7;
void dfs(int node , int parent) {
    dp[node][0] = dp[node][1] = 1;
    for (auto child :adj[node]) {
        if (child == parent)continue;
        dfs(child,node);
        dp[node][1] *= (dp[child][0] + dp[child][1]) % mod;
        dp[node][1] %=mod;
        dp[node][0] *= dp[child][1];
        dp[node][0]%=mod;
    }
}
void solve() {
    cin >> n ;
    for (int i = 0 ; i< n ; i++) {
        dp[i][0] = dp[i][1] = 0  ;
        adj[i].clear();
    }

    for (int i = 1  ; i < n ; i++) {
        int u , v ; cin >> u >> v ;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(0,0);
    cout << (dp[0][0] + dp[0][1]) % mod << endl ;
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

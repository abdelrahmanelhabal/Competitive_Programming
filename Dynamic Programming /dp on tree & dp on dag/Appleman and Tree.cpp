problem link : https://codeforces.com/contest/461/problem/B

#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'
vector<vector<int>>adj;
vector<vector<int>>dp;
vector<int>val;
int n  ;
int const mod = 1e9+7;
void dfs(int node , int parent) {
    dp[node][1]=0;
    dp[node][0]=1;
    for (auto child : adj[node]) {
        if (child == parent)continue;
        dfs(child,node);
        dp[node][1] *= dp[child][0];
        dp[node][1]%=mod;
        dp[node][1] += (dp[child][1] * dp[node][0]) % mod;
        dp[node][1]%=mod;
        dp[node][0] *= dp[child][0];
        dp[node][0]%=mod;
    }
    if (val[node]) {
        dp[node][1] = dp[node][0];
    }
    else {
        dp[node][0] +=dp[node][1];
    }
}
void solve() {
    cin >> n  ;
    adj.assign(n,vector<int>());
    for (int i = 1 ; i < n ; i++) {
        int p ; cin >> p  ;
        adj[p].emplace_back(i);
        adj[i].emplace_back(p);
    }
    val.assign(n,0);
    for (int i = 0 ; i< n ; i++) {
        cin >> val[i];
    }
    dp.assign(n,vector<int>(2,0));
    dfs(0,-1);
    cout << dp[0][1]<< endl;
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

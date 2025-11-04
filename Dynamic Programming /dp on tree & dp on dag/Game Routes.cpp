problem link : https://cses.fi/problemset/task/1681

#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'
int const mod = 1e9+7;
void solve() {
   int n , m ; cin >> n >> m ;
    vector<vector<int>>adj(n);
    vector<int>indeg(n);
    for (int i = 0 ; i < m ; i++) {
        int u , v ; cin >> u >> v ;
        u--,v--;
        adj[u].emplace_back(v);
        indeg[v]++;
    }
    queue<int>q;
    for (int i = 0 ; i< n ; i++) {
        if (indeg[i] == 0) {
            q.emplace(i);
        }
    }
    vector<int>topo;
    while (q.size()) {
        auto node = q.front(); q.pop();
        topo.emplace_back(node);
        for (auto child : adj[node]) {
            indeg[child]--;
            if (indeg[child] == 0) {
                q.emplace(child);
            }
        }
    }
    vector<int>dp(n,0);
    dp[0]=1;
    for (auto node : topo) {
        if (dp[node]==0)continue;
        for (auto child : adj[node]) {
            dp[child] = (dp[node]+dp[child])%mod;
        }
    }
    cout << dp[n-1] << endl ;
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

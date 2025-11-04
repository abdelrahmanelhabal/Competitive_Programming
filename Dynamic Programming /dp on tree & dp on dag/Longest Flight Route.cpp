problem link : https://cses.fi/problemset/task/1680/

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
    vector<int>dp(n,-1e18),parent(n,-1);
    dp[0]=1;
    for (auto node : topo) {
        if (dp[node]==-1e18)continue;
        for (auto child : adj[node]) {
            if (dp[node]+1 > dp[child]) {
                dp[child] = dp[node]+1;
                parent[child]=node;
            }
        }
    }
    if (dp[n-1]==-1e18) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    vector<int>ans;
    int node = n-1;
    while (parent[node]!=-1) {
        ans.emplace_back(node);
        node = parent[node];
    }
    ans.emplace_back(0);
    reverse(all(ans));
    cout << dp[n-1] << endl ;
    for (auto i : ans) {
        cout << i+1 << " " ;
    }
    cout << endl ;
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

#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'
int const mod = 1e9+7;
vector<int>adj[20];
int n , m  , dp[20][(1ll<<20)];
int go(int node , int mask) {
    if (node ==n-1) {
        if (__builtin_popcount(mask) == n) {return 1;}
        return 0;
    }

    int &ret = dp[node][mask];
    if (~ret){return ret;}
    ret = 0 ;
    for (auto child : adj[node]) {
        if (mask & (1<<child)) {continue;}
        ret = ((ret%mod) + (go(child,mask|(1<<child))%mod))%mod;
    }
    return ret;
}
void solve() {
cin >> n >> m ;
    for (int i = 0 ; i < m ; i++) {
        int u , v  ; cin >> u >> v ;
        u--,v--;
        adj[u].emplace_back(v);
    }
    memset(dp,-1,sizeof(dp));
    cout << go(0,1) << endl ;
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int tc = 1;  //cin >> tc ;
    while (tc--) solve();
    return 0;
}

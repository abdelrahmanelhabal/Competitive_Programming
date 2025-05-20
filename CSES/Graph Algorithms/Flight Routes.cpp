#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'
const int INF = 1e18;
void solve() {
    int n , m , k ; cin >> n >> m >> k ;
    vector<vector<pair<int,int>>> adj(n);
    for (int i = 0 ; i < m ; i++) {
        int u , v , w ; cin >> u >> v >> w ;
        u--,v--;
        adj[u].emplace_back(v,w);
    }
    priority_queue<pair<int,int> , vector<pair<int,int>>,greater<>>q;
    q.emplace(0,0);
    vector<vector<int>>dis(n);
    while (!q.empty()) {
        auto [w,node] = q.top(); q.pop();
        if (dis[node].size()>=k){continue;}
        dis[node].emplace_back(w);
        for (auto [child , weight] : adj[node]) {
            if (dis[child].size() < k) {
                q.emplace(w+weight,child);
            }
        }
    }
    for (int i = 0 ; i < k ; i++) {
        cout << dis[n-1][i] << ' ' ;
    }
    cout << endl ;

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

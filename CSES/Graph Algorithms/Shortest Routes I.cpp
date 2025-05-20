#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'
const int INF = 1e18;
void solve() {
int n , m ; cin >>n >>  m ;
    vector<vector<tuple<int,int>>>adj(n);
    for (int i = 0 ; i < m ; i++) {
        int u , v ,  w ; cin >> u >> v >> w ;
        u--,v--; // 0-base
        adj[u].emplace_back(v,w);
    }
    vector<int>dis(n,INF) ;
    priority_queue<pair<int,int>>q;
    q.emplace(0,0);
    dis[0]=0;
    while(!q.empty()) {
        auto [w , node] = q.top(); q.pop();
        w*=-1;
        if (dis[node] < w){continue;}
        for (auto [child , weight] : adj[node]) {
            if (dis[child] > dis[node]+weight) {
                dis[child] = dis[node]+weight;
                q.emplace(-dis[child], child);
            }
        }
    }
    for (int i = 0 ; i < n ; i++) {
        cout << dis[i] << ' ' ;
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

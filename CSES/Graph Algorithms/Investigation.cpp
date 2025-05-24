#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'
const int INF = 1e18 , mod = 1e9+7;
void solve() {
   int n , m  ; cin >> n >> m ;
    vector<vector<tuple<int,int>>>adj(n);
    for (int i = 0 ; i < m ; i++) {
        int u , v  , w ; cin >> u >> v >> w ;
        u--,v--;
        adj[u].emplace_back(v,w);
    }
    vector<int> dis(n,INF) , mx(n,0),mn(n,0) , path(n,0);
    priority_queue<tuple<int,int>>q;
    q.emplace(0,0);
    dis[0]= mn[0] = mx[0]=0;
    path[0]=1;
    while(!q.empty()) {
        auto [w,node] = q.top() ; q.pop();
        w*=-1;
        if (dis[node] < w){continue;}
        for (auto [child,weight] : adj[node]) {
            if (dis[child] > dis[node]+weight) {
                dis[child] = dis[node]+weight;
                path[child] = path[node];
                mx[child] = mx[node]+1;
                mn[child] = mn[node]+1;
                q.emplace(-dis[child],child);
            }
            else if (dis[child] == dis[node]+weight) {
                path[child] = ((path[node]%mod) + (path[child]%mod))%mod;
                mx[child] = max(mx[child],mx[node]+1);
                mn[child] = min(mn[child],mn[node]+1);
            }
        }
    }
    n--;
    cout << dis[n] << " " << path[n] << " " << mn[n] << " " << mx[n] << endl ;
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

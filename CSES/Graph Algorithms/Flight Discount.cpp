/*وَأَنْ لَيْسَ لِلإِنسَانِ إِلَّا مَا سَعَى ۝ وَأَنَّ سَعْيَهُ سَوْفَ يُرَى ۝ ثُمَّ يُجْزَاهُ الْجَزَاءَ الأَوْفَى*/
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
        u--,v--;
        adj[u].emplace_back(v,w);
    }
    vector<vector<int>>dis(n,vector<int>(2,INF)) ;
    priority_queue<tuple<int,int ,int>>q;
    q.emplace(0,0 ,0);
    dis[0][0]=0;
    while(!q.empty()) {
        auto [w , node , discount] = q.top(); q.pop();
        w*=-1;
        if (dis[node][discount] < w){continue;}
        for (auto [child , weight] : adj[node]) {
            if (dis[child][discount] > dis[node][discount]+weight) {
                dis[child][discount] = dis[node][discount]+weight;
                q.emplace(-dis[child][discount], child , discount);
            }
            if (discount == 0) {
                if (dis[child][1] > dis[node][discount]+(weight/2)) {
                    dis[child][1] = dis[node][discount]+(weight/2);
                    q.emplace(-dis[child][1], child , 1);
                }
            }
        }
    }
    cout << dis[n-1][1] << endl ;
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

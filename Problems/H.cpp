/*وَأَنْ لَيْسَ لِلإِنسَانِ إِلَّا مَا سَعَى ۝ وَأَنَّ سَعْيَهُ سَوْفَ يُرَى ۝ ثُمَّ يُجْزَاهُ الْجَزَاءَ الأَوْفَى*/
#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define lower(s) (transform(s.begin(), s.end(), s.begin(), ::tolower));
#define str string
#define ll long long
#define ld long double
#define YES cout << "YES" << endl;
#define Yes cout << "Yes" << endl;
#define NO cout << "NO" << endl;
#define No cout << "No" << endl;
#define endl '\n'
#define F first
#define S second
constexpr ll  N = 1e3+5, mod = 1e9+7 , INF = 1e18, zero = 0 , one = 1 , two = 2, there = 3;
ll dx[] = {1, -1 , 0 , 0 , 0 , 0 };
ll dy[] = {0 , 0 , 1 , -1, 0 , 0 };
ll dz[] = {0 , 0 , 0 , 0 , 1, -1};

void solve() {
ll n , m ; cin >> n >> m ;
    vector<set<ll>>adj(n+1);
    vector<ll>deg(n+1);
    for (int i = 0 ; i < m ; i++) {
        ll from , to ; cin >> from >> to;
        adj[from].emplace(to);
        adj[to].emplace(from);
        deg[to]++;
        deg[from]++;
    }
    ll ans = INF;

   for (int node1 = 1; node1 <=n ; node1++) {
       for (auto node2 : adj[node1]) {
           if (node2 > node1) {
               for (auto node3 : adj[node2]) {
                   if (node3 > node2 && adj[node1].count(node3)) {
                       ll sum = (deg[node1]+deg[node2]+deg[node3]-6);
                       ans = min(ans,sum);
                   }
               }
           }
       }
   }
    if (ans == INF){cout << -1 << endl ;}
    else{cout << ans << endl ;}
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int tc = one; //cin >> tc;
    while (tc--) { solve(); }
    return 0;
}
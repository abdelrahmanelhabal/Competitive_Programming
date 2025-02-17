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
vector<vector<ll>>adj;
map<ll,ll> vis;
void dfs(ll node) {
    vis[node]=1;
    for (auto child : adj[node]) {
        if (!vis[child]) {
            dfs(child);
        }
    }
}
void solve() {
ll n ; cin >> n ;
    vector<ll>x(n),y(n);
    for (int i = 0 ;  i < n  ; i++) {
        cin >> x[i] >> y[i];
    }
    adj.assign(n+1,vector<ll>());
    for (int i = 0 ; i < n ; i++) {
        for (int j = i +1 ; j < n ; j++) {
            if (x[i]==x[j] || y[i] == y[j]) {
                adj[i].emplace_back(j);
                adj[j].emplace_back(i);
            }
        }
    }
    ll ans = 0 ;
    for (int i = 0;i < n ; i++) {
        if (!vis[i]) {
            dfs(i);
            ans++;
        }
    }
    cout << ans-1 << endl ;

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
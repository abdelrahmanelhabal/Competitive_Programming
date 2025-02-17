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
char grid[11][11][11];
ll k , n , m , cnt ;
ll vis[11][11][11];
bool valid(ll z , ll i , ll j) {
    return z >=0 && z < k && i >=0 && i < n && j < m && j >=0 && grid[z][i][j]!='#' && !vis[z][i][j];
}
void dfs(ll z , ll i , ll j){
    if (!valid(z, i, j)) return;
    cnt++;
    vis[z][i][j]=1;
    for (int k = 0 ; k < 6 ; k++) {
        dfs(dz[k]+z,dx[k]+i,dy[k]+j);
    }
}
void solve() {
    cin >> k >> n >> m  ;
    for (int i = 0 ; i < k ; i++) {
        for (int j =  0;  j < n ; j++) {
            for (int l = 0 ; l < m ; l++) {
                cin >> grid[i][j][l];
            }
        }
    }
    ll x , y ; cin >> x >> y ;
    x--;y--;
    dfs(0,x,y);
    cout << cnt << endl ;
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
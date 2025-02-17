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
char grid[3][150];
ll vis[3][150];
ll n , can;
void dfs(ll i ,ll j) {
    if (j >= n-1) { can = 1; return; }
    vis[i][j]=1;
    if (grid[i][j+1]!='.'){return;}
    if (i+1>=0 && i+1 < 3 && grid[i+1][j+1]=='.' && grid[i+1][j+2] == '.'&& grid[i+1][j+3] == '.') {
        dfs(i+1,j+3);
    }
    if (i-1>=0 && i-1 < 3 && grid[i-1][j+1]=='.' && grid[i-1][j+2] == '.'&& grid[i-1][j+3] == '.') {
        dfs(i-1,j+3);
    }
    if (!vis[i][j+3]&&grid[i][j+1]=='.' && grid[i][j+2] == '.'&& grid[i][j+3] == '.') {
        dfs(i,j+3);
    }
}
void solve() {
ll k ; cin >> n >> k  ;
    can = 0 ;
    pair<ll,ll> st;
    for (int i = 0 ; i < 3 ; i++) {
        str s ; cin >> s  ;
        for (int j = 0 ; j < n ; j++) {
            grid[i][j] = s[j];
            vis[i][j]=0;
            if (grid[i][j]=='s') { st = {i,j}; }
        }
    }
    for (int i = 0 ; i < 3 ; i++) {
        for (int j = n ; j  < n+6 ;j++) {
            grid[i][j]='.';
        }
    }
    dfs(st.F,st.S);
    if (can){YES}
    else{NO}
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int tc = one; cin >> tc;
    while (tc--) { solve(); }
    return 0;
}
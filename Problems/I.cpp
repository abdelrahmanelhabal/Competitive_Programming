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
ll n , a, b ; cin >> n >> a >> b ;
    if (a == 1 && b == 1  && n <= 3 && n !=1){cout << "NO" << endl ;return;}
    if (a > 1 && b > 1 ) {cout << "NO" << endl ;return;}
    vector<vector<ll>>adj(n+1,vector<ll>(n+1,0));
    ll cnt = n - max(a,b);

    for (int i = 1 ; i <= cnt ; i++) {
        adj[i][i+1]=adj[i+1][i]=1;
    }

    cout << "YES" << endl ;
    for (int i = 1 ; i <=n ; i++) {
        for (int j = 1 ; j <=n ; j++) {
            if (i == j){cout << adj[i][j] ; continue;}
            if (a > b){cout << adj[i][j];}
            else{cout << (adj[i][j]?0:1);}
        }
       cout << endl ;
    }
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
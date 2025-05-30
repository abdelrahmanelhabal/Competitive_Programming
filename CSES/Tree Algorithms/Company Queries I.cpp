#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'
const int Log = 30 , N = 2e5+5;
int n , q , parent[N] , up[N][Log] ;
void build() {
    for (int i =1 ; i <= n ; i++) {
        up[i][0]=parent[i];
    }
    for (int j = 1 ; j < Log ;j++) {
        for (int i = 1; i <=n ; i++) {
            up[i][j] = up[up[i][j-1]][j-1];
        }
    }
}
int kth_ancestor(int node , int k) {
    for (int i = 0 ; i < Log ; i++) {
        if (k >> i & 1) {
            node = up[node][i];
        }
    }
    return node;
}
void solve() {
    cin >> n >> q ;
    for (int i = 2 ; i <=n ; i++) {
        int par ; cin >> par ;
        parent[i] = par ;
    }
    build();
    while (q--) {
        int u , k ; cin >> u >> k ;
        int ans = kth_ancestor(u,k) ;
        cout << (ans? ans : -1) << endl ;
    }

}

signed main() {
    #ifndef ONLINE_JUDGE
         freopen("input.txt", "r", stdin);
       freopen("output.txt", "w", stdout);
     #endif
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int tc =1;  //cin >> tc ;
    while (tc--) solve();
    return 0;
}

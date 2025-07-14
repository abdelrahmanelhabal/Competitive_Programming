#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'

void solve(){
    int n , m  ; cin >> n >> m ;
    multiset<int> a ;
    for (int i = 0 ; i < n ; i++) {
        int x ; cin >> x  ;
        a.insert(x) ;
    }
    for (int i = 0 ; i < m ; i++) {
        int x ; cin >> x ;
        auto it = a.upper_bound(x);
        if (it == a.begin()) {
            cout << -1 << endl ;
        }
        else {
            cout << *prev(it) << endl ;
            a.erase(prev(it)) ;
        }
    }

}

signed main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int tc = 1; //cin >> tc ;
    while (tc--) solve();
    return 0;
}
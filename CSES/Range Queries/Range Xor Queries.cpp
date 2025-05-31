#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'

void solve() {
    int n , q  ; cin >> n >>  q;
    vector<int>a(n);
    for (int i = 0 ; i < n ; i++) {
        cin >> a[i];
    }
    vector<int>pre(n);
    pre[0]=a[0];
    for (int i = 1; i < n ; i++) {
        pre[i] = pre[i-1]^a[i];
    }
    while (q--) {
        int l , r ; cin >> l >> r ;
        l--,r--;
        cout << (pre[r] ^ (l > 0 ? pre[l-1] : 0)) << endl ;
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

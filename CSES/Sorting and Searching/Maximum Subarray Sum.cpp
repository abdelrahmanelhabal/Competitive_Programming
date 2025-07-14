#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'

void solve(){
    int n ; cin >> n ;
    int sum = 0 , mx = -1e18 ;
    for (int i = 0 ; i < n ; i++) {
        int a ; cin >> a ;
        sum += a ;
        mx = max(mx,sum);
        sum = max(sum,0ll);
    }
    cout << mx << endl ;
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
#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'

void solve(){
    int n  , x ; cin >> n >> x  ;
    vector<int>a(n);
    for (int i = 0 ; i < n ; i++) {
        cin >> a[i];
    }
    sort(all(a));
    int l = 0 , r = n-1 , ans = 0;
    while (l<=r) {
        if (a[l] + a[r] <= x) {
            ans++;
            l++;
            r--;
        }
        else {
            ans++;
            r--;
        }
    }
    cout << ans << endl ;

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
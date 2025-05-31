#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'

void solve() {
int n ; cin >> n ;
    vector<int>a(n);
    for (int i = 0 ; i< n ; i++) { cin >> a[i]; }
    int ans = 1e18;
    for (int mask = 0 ; mask < (1<<n) ; mask++) {
        int group1 = 0, group2 = 0;
        for (int j = 0 ; j < n ; j++) {
            if (mask & (1<< j)) {
                group1 += a[j];
            }
            else {
                group2 += a[j];
            }
        }
        ans = min(ans, abs(group1 - group2));
    }
    cout << ans << endl ;
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

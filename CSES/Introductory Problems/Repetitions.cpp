#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'

void solve() {
str s ; cin >>  s;
    int n = s.size();
    int ans = 0 , cnt = 0  ; char curr = s[0];
    for (int i = 0 ; i < n ; i++) {
        if (s[i] == curr) {
            cnt++;
        }
        else {
            ans = max(ans,cnt);
            curr = s[i];
            cnt=1;
        }
    }
    ans = max(ans,cnt);
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

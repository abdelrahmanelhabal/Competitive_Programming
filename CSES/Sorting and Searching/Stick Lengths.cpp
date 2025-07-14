#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'

void solve(){
    int n ; cin >> n ;
    vector<int>a(n);
    for (int i = 0 ; i < n ; i++) {
        cin >> a[i];
    }
    sort(all(a));
    int mid = a[n/2];
    int ans = 0 ;
    for (int i = 0 ; i < n ; i++) {
        ans+= abs(mid-a[i]);
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
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
    multiset<int>s ;
    for (int i = 0 ; i < n ; i++) {
        auto it = s.upper_bound(a[i]);
        if (it != s.end()) {
            s.erase(it);
        }
        s.insert(a[i]);
    }
    cout << s.size() << endl ;
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
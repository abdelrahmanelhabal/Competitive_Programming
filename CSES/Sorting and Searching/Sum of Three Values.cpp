#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'
void solve() {
    int n , x  ; cin >> n >> x ;
    vector<int>a(n);
    for (int i = 0 ; i < n ; i++) {
        cin >> a[i];
    }
    map<int,int> idx ;
    for (int i = 0 ; i < n ; i++) {
        for (int j = i+1 ; j < n  ; j++) {
            int target = x - a[i] - a[j];
            if (idx.count(target) && i != idx[target] && j != idx[target]) {
                cout << i+1 << " " << j+1 << ' ' << idx[target]+1 << endl ;
                return;
            }
        }
        idx[a[i]]=i;
    }
    cout << "IMPOSSIBLE" << endl ;
}


signed main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int tc =1; // cin >> tc ;
    while (tc--) solve();
    return 0;
}

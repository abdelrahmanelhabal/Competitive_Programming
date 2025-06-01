#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define ll long long
#define ld long double
#define endl '\n'
void solve() {
    int n , x  ; cin >> n >> x ;
    vector<int>a(n);

    for (int i = 0 ; i < n ; i++) {
        cin >> a[i];
    }
    map<int,pair<int,int>> idx ;
    for (int i = 0 ; i < n ; i++) {
        for (int j = i+1 ; j < n  ; j++) {
                int target = x - a[i] - a[j] ;
                if (idx.count(target)) {
                    int k  = idx[target].first , l = idx[target].second ;
                    if (i != k && i != l && j != k && j != l) {
                        cout << i+1 << " " << j+1 << " " << k+1 << " " << l+1<< endl ;
                        return;
                    }
                }
        }
        for (int j = i+1 ; j < n ;j++) {
            idx[a[i]+a[j]] = {i,j};
        }
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

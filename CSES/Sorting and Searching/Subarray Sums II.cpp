#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'

void solve() {
int n , x ; cin >> n >> x ;
    map<int,int> freq;
    int prefix = 0 , ans = 0 ;
    freq[0]=1;
    for (int i = 0 ; i < n ; i++) {
        int a ; cin >> a;
        prefix += a;
        ans+= freq[prefix-x];
        freq[prefix]++;
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

#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'
void solve() {
    int n , k ; cin >> n >> k ;
    vector<int> a(n);
    for (int i = 0 ; i < n ; i++) { cin >> a[i]; }
    map<int,int> freq;
    int ans = 0 , j = 0 ;
    for (int i = 0 ; i < n ;i++) {
        freq[a[i]]++;
        while (j < n && freq.size() > k) {
            freq[a[j]]--;
            if (freq[a[j]]==0)freq.erase(a[j]);
            j++;
        }
        ans += i - j + 1;
    }
    cout << ans << endl ;
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

probelm link : https://codeforces.com/contest/2121/problem/E

#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'
str a , b ;
int l , r  , dp[10][2][2];
int go(int i, int lowerBound , int upperBound ) {
    if (i == a.size()) {
        return 0 ;
    }
    int &ret = dp[i][lowerBound][upperBound];
    if (~ret){return ret;}
    int start = (lowerBound ? a[i]-'0':0);
    int end = (upperBound ? b[i]-'0':9);
    ret = 1e18 ;
    for (int j = start ; j <= end ; j++) {
        int gain = ((a[i]-'0') == j) + ((b[i]-'0') == j);
        int res = go(i+1,(lowerBound && start == j),(upperBound && end == j)) + gain;
        ret = min(res,ret);
    }
    return ret;
}
void solve() {
    cin >> l >> r ;
    memset(dp, -1, sizeof(dp));
    a = to_string(l);
    b = to_string(r);
    a = str("0",b.size()-a.size()) + a;
    int ans = go(0,1,1);
    cout << ans << endl ;
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int tc = 1; cin >> tc;
    while (tc--) solve();
    return 0;
}

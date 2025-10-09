problem link : https://codeforces.com/contest/204/submission/342730411

#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'
str a ;
int l , r , dp[19][2][11][11];
int go(int i , int flag , int first,int last ) {
    if (i == a.size()) {
        return (first == last && first != 0);
    }
    int &ret = dp[i][flag][first][last];
    if (~ret){return ret;}

    int end = (flag ? a[i]-'0' : 9);
    ret = 0 ;
    for (int j = 0 ; j <= end ; j++) {
        ret+=go(i+1,(flag && (j == end)),(first == 0 ? j : first),j);
    }
    return ret;
}
void solve() {
    cin >> l >> r ;
    a = to_string(r);
    memset(dp,-1,sizeof(dp));
    int ans = go(0,1,0,0);
    a = to_string(l-1);
    memset(dp,-1,sizeof(dp));
    ans -= go(0,1,0,0);
    cout << ans <<endl ;

}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int tc = 1; //cin >> tc;
    while (tc--) solve();
    return 0;
}


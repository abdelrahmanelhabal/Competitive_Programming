problem link : https://cses.fi/problemset/task/1158/

#include<bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define int long long
#define endl '\n'
void solve() {
  int n , x ; cin >> n >> x ;
  vector<int>h(n),s(n);
  for (int i = 0 ; i< n ; i++) {
    cin >> h[i];
  }
  for (int i = 0 ; i< n ; i++) {
    cin >> s[i];
  }
  vector<int>dp(x+1,0);
  dp[x] = 0 ;
  for (int i = 0 ; i< n ; i++) {
    for (int j = x ; j >= h[i] ;j--) {
        dp[j] = max(dp[j - h[i]] + s[i], dp[j]);
    }
  }
  int ans = 0 ;
  for (int i = 0 ; i<= x ; i++) ans = max(ans, dp[i]);
  cout << ans << endl ;
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


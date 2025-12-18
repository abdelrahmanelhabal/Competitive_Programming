problem link : https://atcoder.jp/contests/dp/tasks/dp_c

#include<bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define int long long
#define endl '\n'

void solve() {
  int n ; cin >> n ;
  vector<int>a(n+1) , b(n+1) , c(n+1);
  for (int i = 1 ; i<=n ; i++) {
    cin >> a[i] >> b[i] >> c[i];
  }
  vector<vector<int>>dp(n+1,vector<int>(3,0));

  for (int i = n ; i >= 1 ; i-- ) {
      dp[i][0] = a[i] ; dp[i][1] = b[i] ; dp[i][2] = c[i];
      if (i + 1 <= n) {
        dp[i][0] = max({dp[i][0] , dp[i+1][1] + a[i] , dp[i+1][2] + a[i]});
        dp[i][1] = max({dp[i][1] , dp[i+1][0] + b[i] , dp[i+1][2] + b[i]});
        dp[i][2] = max({dp[i][2] , dp[i+1][1] + c[i] , dp[i+1][0] + c[i]});
      }
  }
  cout << max({dp[1][0] , dp[1][1] , dp[1][2]}) << endl ;
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


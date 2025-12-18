problem link : https://cses.fi/problemset/task/1638/

#include<bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define int long long
#define endl '\n'
int const mod = 1e9+7;
void solve() {
  int n ; cin >> n ;
  vector<string>grid(n);
  for (int i = 0 ; i < n ; i++) cin >> grid[i];

  vector<vector<int>>dp(n,vector<int>(n,0));
  dp[0][0] = grid[0][0] == '.' ;
  for (int i = 0 ; i< n ; i++) {
    for (int j = 0 ; j < n ; j++) {
      if (i + 1 < n && grid[i+1][j] == '.') {
        dp[i+1][j] = (dp[i+1][j] + dp[i][j]) % mod;
      }
      if (j + 1 < n && grid[i][j+1] == '.') {
        dp[i][j+1] = (dp[i][j+1] + dp[i][j]) % mod ;
      }
    }
  }
  cout << dp[n-1][n-1] << endl ;
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


problem link : https://cses.fi/problemset/task/1634/

#include<bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define int long long
#define endl '\n'

void solve() {
  int n , x ; cin >> n >> x ;
  vector<int>c(n);
  for (int i = 0 ; i< n ; i++) {
    cin >> c[i];
  }
  vector<int>dp(x+1,1e18);
  dp[x] = 0 ;
  for (int i = x ; i >= 0 ; i--) {
    for (int j = 0 ; j < n ; j++) {
      if (i - c[j] >= 0) {
        dp[i - c[j]] = min(dp[i - c[j]] , dp[i] + 1);
      }
    }
  }
  cout << (dp[0] == 1e18 ? -1 : dp[0]) << endl ;
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


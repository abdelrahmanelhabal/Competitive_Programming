problem link : https://cses.fi/problemset/task/1637/ 

#include<bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define int long long
#define endl '\n'

void solve() {
  int n ; cin >> n ;
  vector<int>dp(n+1,1e18);
  dp[n] = 0 ;
  for (int i = n ; i >= 0 ; i--) {
    string s = to_string(i);
    for (int j = 0 ; j < s.size() ; j++) {
      int d = s[j] - '0';
      if (d) dp[i - d] = min(dp[i - d] , dp[i] + 1);
    }
  }
  cout << dp[0] << endl ;
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


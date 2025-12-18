problem link : https://atcoder.jp/contests/dp/tasks/dp_b

#include<bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define int long long
#define endl '\n'
int const mod = 1e9+7;
void solve() {
  int n , k ; cin >> n >> k ;
  vector<int>h(n);
  for (int i = 0 ; i < n ; i++) {
    cin >> h[i];
  }
  vector<int>dp(n,1e18);
  dp[0] = 0 ;
  for (int i = 0 ; i< n ; i++) {
    for (int j = 1 ; j <= k ; j++) {
      if (i + j < n) {
        dp[i + j] = min(dp[i + j] , dp[i] + abs(h[i] - h[i + j]));
      }
    }
  }
  cout << dp[n-1] << endl ;
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


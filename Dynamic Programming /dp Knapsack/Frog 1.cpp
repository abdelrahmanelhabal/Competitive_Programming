problem link : https://atcoder.jp/contests/dp/tasks/dp_a

#include<bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define int long long
#define endl '\n'
int const mod = 1e9+7;
void solve() {
  int n ; cin >> n ;
  vector<int>h(n);
  for (int i = 0 ; i < n ; i++) {
    cin >> h[i];
  }
  vector<int>dp(n,1e18);
  dp[0] = 0 ;
  for (int i = 0 ; i< n ; i++) {
    if (i + 1 < n) {
      dp[i + 1] = min(dp[i+1] , dp[i] + abs(h[i] - h[i+1]));
    }
    if (i + 2 < n) {
      dp[i + 2] = min(dp[i + 2] , dp[i] + abs(h[i] - h[i+2]));
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


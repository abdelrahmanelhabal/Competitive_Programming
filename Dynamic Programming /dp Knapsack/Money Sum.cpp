problem link : https://cses.fi/problemset/task/1745/

#include<bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define int long long
#define endl '\n'
void solve() {
  int n ; cin >> n ;
  vector<int>c(n);
  int x = 0 ;
  for (int i = 0 ; i< n ; i++) {
      cin >> c[i];
      x+=c[i];
  }
  vector<int>dp(x+1,0);

  dp[0] = 1 ;
  for (int i = 0 ; i < n ; i++) {
    for (int j = x ; j >= c[i] ; j--) {
        dp[j] = max(dp[j],dp[j - c[i]]);
    }
  }
  cout << count(all(dp),1) - dp[0] << endl ;
  for (int i = 1 ; i <= x ; i++)
      if (dp[i]) cout << i << " ";
  cout << endl ;
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


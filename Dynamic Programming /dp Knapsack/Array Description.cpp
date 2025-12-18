problem link : https://cses.fi/problemset/task/1746/

#include<bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define int long long
#define endl '\n'
int const mod = 1e9+7;
void solve() {
  int n , m ; cin >> n >> m ;
  vector<int>a(n+1);
  for (int i = 1 ; i<= n ; i++) {
    cin >> a[i];
  }
  vector<vector<int>>dp(n+1,vector<int>(m+5,0));
  if (a[n]) {
    dp[n][a[n]]=1;
  }
  else {
    for (int prev = 1 ; prev <= m ; prev++)  dp[n][prev]=1;
  }
  for (int i = n-1 ; i >= 1 ; i--) {
    if (a[i]) {
      int val =a[i] ;
      dp[i][val] += (dp[i+1][val] + dp[i+1][val-1] + dp[i+1][val+1]) % mod;
      continue;
    }
    for (int prev = 1 ; prev <= m ; prev++) {
      dp[i][prev] += (dp[i+1][prev] + dp[i+1][prev-1] + dp[i+1][prev+1]) % mod;
      dp[i][prev] %= mod ;
    }
  }
  int ans = 0 ;
  if (a[1]) {
    int val = a[1];
    ans = (dp[1][val] + dp[1][val-1] + dp[1][val+1]) % mod;
  }
  else {
    for (int i = 1 ; i<= m ; i++)
      ans = (ans +  dp[1][i]) % mod ;
  }
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


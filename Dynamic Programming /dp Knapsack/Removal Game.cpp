problem link : https://cses.fi/problemset/task/1097/

#include<bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define int long long
#define endl '\n'
void solve() {
  int n ; cin >> n ;
  vector<int>a(n);
  for (int i = 0 ; i < n ; i++) {
    cin >> a[i];
  }

  vector<vector<pair<int,int>>>dp(n,vector<pair<int,int>>(n,{-1e18,-1e18}));
  for (int len = 1 ; len <= n ; len++) {
    for (int l = 0 ; l <=n - len ; l++) {
      int r = l + len - 1 ;
      int turn = (n - len) % 2 ;

      if (l == r) {
        if (turn)
          dp[l][r] = {a[l],0};
        else
          dp[l][r] = {0,a[l]};
        continue;
      }
      if (turn) {
        pair<int,int> ch1 = dp[l+1][r] ;
        ch1.first += a[l];
        pair<int,int> ch2 = dp[l][r-1] ;
        ch2.first += a[r];
        if (ch1.first > ch2.first) {
          dp[l][r] = ch1 ;
        }
        else {
          dp[l][r] = ch2 ;
        }
      }
      else {
        pair<int,int> ch1 = dp[l+1][r] ;
        ch1.second += a[l];
        pair<int,int> ch2 = dp[l][r-1] ;
        ch2.second += a[r];
        if (ch1.second > ch2.second) {
          dp[l][r] = ch1 ;
        }
        else {
          dp[l][r] = ch2;
        }
      }
    }
  }
  cout << dp[0][n-1].second << endl ;
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


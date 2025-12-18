problem link : https://cses.fi/problemset/task/1093/

#include<bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define int long long
#define endl '\n'
int const mod = 1e9+7;
void solve() {
  int n ; cin >> n ;
  int sum = n * (n + 1) / 2 ;
  if (sum & 1) {
    cout << 0 << endl ;
    return;
  }
  int target = sum / 2 ;
  int inv2 = (mod + 1)/2;
  vector<int>dp(target+1,0);
  dp[0] = 1 ;
  for (int i = 1 ; i <=n ; i++) {
    for (int j = target ; j >= i ; j--) {
      dp[j] = (dp[j] + dp[j - i]) % mod ;
    }
  }
  cout << (dp[target] * inv2) % mod << endl ;
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


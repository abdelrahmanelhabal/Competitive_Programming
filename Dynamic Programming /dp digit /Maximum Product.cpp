problem link : https://codeforces.com/gym/100886/problem/G

#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'
int l , r  ;
int dp[19][2][2][2];
str a , b ;
int go(int i , int lb , int ub, int z) {
    if (i == b.size()) {
        return 1;
    }
    int &ret=dp[i][lb][ub][z];
    if (~ret){return ret;}
    int s = (lb ? a[i]-'0':0);
    int e = (ub ? b[i]-'0':9);
    int res = 0 ;
    for (int j = s ; j <= e ; j++) {
        if (z && j == 0) {
            res= go(i+1, (lb && (j == a[i]-'0')) , (ub && (j == b[i]-'0')), z) ;
        }
        else {
            res=go(i+1, (lb && (j == a[i]-'0')) , (ub && (j == b[i]-'0')) , 0) *j;
        }
        ret = max(ret,res);
    }
    return ret;
}
void build(int i , int lb , int ub, int z) {
    if (i == b.size()) { return ; }
    int s = (lb ? a[i]-'0':0);
    int e = (ub ? b[i]-'0':9);
    int curr = dp[i][lb][ub][z];
    for (int j = s ; j <= e ; j++) {
        if (z && j == 0) {
            int next = go(i+1, (lb && (j == a[i]-'0')) , (ub && (j == b[i]-'0')) , 0);
            if (next == curr) {
                build(i+1, (lb && (j == a[i]-'0')) , (ub && (j == b[i]-'0')), z) ;
                return;
            }
        }
        int next = go(i+1, (lb && (j == a[i]-'0')) , (ub && (j == b[i]-'0')) , 0) *j;
        if (curr == next) {
            cout << j ;
            build(i+1, (lb && (j == a[i]-'0')) , (ub && (j == b[i]-'0')) , 0);
            return;
        }
    }
}
void solve() {
    cin >> l >> r ;
    b = to_string(r);
    a = to_string(l);
    a = str(b.size()-a.size(),'0') + a;
    memset(dp,-1,sizeof(dp));
    go(0,1,1,1);
    build(0,1,1,1);
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

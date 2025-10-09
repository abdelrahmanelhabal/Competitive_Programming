problem link : https://codeforces.com/contest/1073/my

#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'
int const mod = 998244353;
int l , r , k ;
str a ;
int dp1[19][2][2][2049] , dp2[19][2][2][2049];
int fast_pow(int base, int power){
    int res = 1;
    base = base % mod;
    if (base == 0) return 0;
    while (power > 0)
    {
        if (power & 1)
            res = (res*base) % mod;
        power = power>>1;
        base = (base*base) % mod;
    }
    return res;
}
int go1(int i, int flag , int z , int mask) {
    if (i == a.size()) {
        return __popcount(mask)<=k;
    }
    int &ret = dp1[i][flag][z][mask];
    if (~ret){return ret;}
    int end = (flag ? a[i]-'0':9);
    ret = 0 ;
    for (int j = 0 ; j <=end ; j++) {
        if (z && j ==0 ) {
            ret += go1(i+1,flag && (j == end),z,mask);
            ret%=mod;
        }
        else {
            int new_mask = mask | (1<<j);
            ret+=go1(i+1,flag && (j == end),0,new_mask);
            ret%=mod;
        }
    }
    return ret%mod;
}
int go2(int i , int flag , int z , int mask ) {
    if (i == a.size()) {
        return 0;
    }
    int &ret = dp2[i][flag][z][mask];
    if (~ret){return ret;}
    int end = (flag ? a[i]-'0':9);
    ret = 0 ; int len = a.size();
    for (int j = 0 ; j <=end ; j++) {
        if (z && j ==0 ) {
            ret += go2(i+1,flag && (j == end),z,mask);
            ret%=mod;
        }
        else {
            int new_mask = mask | (1<<j);
            int cnt = go1(i+1,flag && (j == end),0,new_mask) % mod;
            ret += go2(i+1,flag && (j == end),0,new_mask);
            ret%=mod;
            int add =((j%mod) * (fast_pow(10,len-i-1)%mod))%mod;
            add = (add * cnt)%mod;
            ret+=add;
            ret%=mod;
        }
    }
    return ret;
}
void solve() {
    cin >> l >> r >> k ;
    a = to_string(r);
    memset(dp1,-1,sizeof(dp1));
    memset(dp2,-1,sizeof(dp2));
    int ans = go2(0,1,1,0);
    a = to_string(l-1);
    memset(dp1,-1,sizeof(dp1));
    memset(dp2,-1,sizeof(dp2));
    ans -= go2(0,1,1,0);
    cout << (ans+mod)%mod << endl ;
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


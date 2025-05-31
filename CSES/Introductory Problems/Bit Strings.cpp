#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'
int const mod = 1e9+7;
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
void solve() {
int n ; cin >> n ;
    cout << fast_pow(2, n) << endl ;
}


signed main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int tc =1;  //cin >> tc ;
    while (tc--) solve();
    return 0;
}

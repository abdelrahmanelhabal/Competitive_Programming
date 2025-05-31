ll fast_pow(ll base, ll power){
    ll res = 1;
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

ll sub(ll const a , ll const b){ return ((a%mod) - (b%mod) + mod) % mod; }
ll add(ll const a, ll const b) {return ((b % mod) + (a % mod)) % mod;}
ll mul(ll a,ll b){ return ((a%mod)*(b%mod))%mod; }
ll divide(ll a,ll b){return mul(a,fast_pow(b,mod-2));}

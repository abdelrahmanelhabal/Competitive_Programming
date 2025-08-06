// calc a^n using only o(log n)

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
vector<int> sieve(int limit) {
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p * p <= limit; ++p) {
        if (is_prime[p]) {
            for (int i = p * p; i <= limit; i += p) {
                is_prime[i] = false;
            }
        }
    }
    vector<int> primes;
    for (int p = 2; p <= limit; ++p) {
        if (is_prime[p]) {
            primes.push_back(p);
        }
    }
    return primes;
}

vector<ll> segmented_sieve(ll l, ll r) {
    if (l == 1) {
        l++;
    }
    int limit = sqrtl(r);
    while ((ll) limit * limit <= r) limit++;
    while ((ll) limit * limit > r) limit--;
    auto primes = sieve(limit);
    vector<bool> is_prime(r - l + 1, true);
    for (ll p : primes) {
        ll start = max((ll)p * p, (ll)(l + p - 1) / p * p);
        for (ll j = start; j <= r; j += p) {
            is_prime[j - l] = false;
        }
    }
    vector<ll> vec;
    for (ll i = l; i <= r; ++i) {
        if (is_prime[i - l]) {
            vec.push_back(i);
        }
    }
    return vec;
}

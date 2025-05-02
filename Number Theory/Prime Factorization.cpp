/* Find all prime factor in o(sqrt(n)) */
vector<ll> prime_factorization(ll n) {
    vector<ll> prime;
    for (int i = 2; i*i <= n ; i++) {
        while (n % i == 0) {
            prime.push_back(i);
            n /= i;
        }
    }
    if (n !=1) { prime.push_back(n); }
    return prime;
}


/* Find all prime factor in o(log(n)) */
vector<ll> seive(ll n) { 
    vector<ll>prime , divide(n+1);
    vector<bool> is_prime(n+1,true);
    is_prime[0]=is_prime[1]=false;
    for (int i = 2 ; i <= n ; i++) {
        if (is_prime[i]) {
            prime.push_back(i);
            divide[i]=i;
            for (int j = 2 * i ; j <= n ; j+=i) {
                is_prime[j]=false;
                if (divide[j]==0) {
                    divide[j]=i;
                }
            }
        }
    }
    return divide;
}
vector<ll> prime_factorization(ll n, vector<ll>&divide) {
    vector<ll>prime;
    while (n > 1) {
        ll div = divide[n];
        prime.emplace_back(div);
        n/=div;
    }
    return prime;
}
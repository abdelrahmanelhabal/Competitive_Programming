/* find all primes form 1 to n  in  o(n log(n)) */
vector<ll>seive(ll n) {
    vector<ll>prime;
    vector<bool> is_prime(n+1,true);
    is_prime[0]=is_prime[1]=false;
    for (int i = 2 ; i <= n ; i++) {
        if (is_prime[i]) {
            prime.push_back(i);
            for (int j = 2 * i ; j <= n ; j+=i) {
                is_prime[j]=false;
            }
        }
    }
    return prime;
}
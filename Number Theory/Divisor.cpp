/* find all  divisor in  o(sqrt(n))*/
vector<ll> div(ll n) {
    vector<ll>divisors;
    ll i
    for (i = 1; i *i < n ; i++) {
        if (n%i == 0) {
                divisors.push_back(i);
                divisors.push_back(n/i);
        }
    }
    if (i*i == n) { divisors.push_back(i); }
    sort(divisors.begin(), divisors.end());
    return divisors;
}

/* generate divisors for all number from 1 to 1e5 in o(nlog(n))*/
int const N = 1e5 ;
vector<int> divs[N+1];
void generate() { 
    for (int i = 1; i <=N; i++) {
        for (int j = i ;  j<=N ; j+=i){
            divs[j].emplace_back(i);
        }
    }
}
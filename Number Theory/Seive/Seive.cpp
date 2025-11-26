int const N = 1e8;
vector<int>primes ;
bitset<N+1> isPrime;
void init() {
  isPrime.set();
  isPrime[0] = isPrime[1] = 0;
  for (int i = 2; i * i <= N; i++) {
    if (isPrime[i]) {
      for (int j = i * i; j <= N; j += i) {
        isPrime[j] = false;
      }
    }
  }
  for (int i = 2; i <= N; i++) {
    if (isPrime[i]) primes.push_back(i);
  }
}

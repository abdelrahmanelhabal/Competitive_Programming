vector<int> prime_factorization(int n) {
  vector<int> prime;
  for (int i = 2; i*i <= n ; i++) {
    while (n % i == 0) {
      prime.push_back(i);
      n /= i;
    }
  }
  if (n !=1) { prime.push_back(n); }
  return prime;
}

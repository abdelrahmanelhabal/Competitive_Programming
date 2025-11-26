int const N = 1e5 ;
int spf[N+5];
void seive() {
  for (int i = 2 ; i < N ; i++) spf[i] = i ;
  for (int i = 2 ; i < N ; i++) {
    if (spf[i] == i) {
      for (int j = i ; j < N ; j +=i) spf[j] = min(spf[j],i);
    }
  }
}
vector<int>prime_factorization(int n) {
  vector<int>res;
  while (n > 1) {
    res.push_back(spf[n]);
    n/=spf[n];
  }
  return res;
}


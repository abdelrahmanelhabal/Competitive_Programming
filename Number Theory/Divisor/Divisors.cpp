vector<int> divisors(int n) {
  vector<int>res;
  int i ;
  for (i = 1; i *i < n ; i++) {
    if (n%i == 0) {
      res.emplace_back(i);
      res.emplace_back(n/i);
    }
  }
  if (i*i == n) { res.emplace_back(i); }
  sort(res.begin(), res.end());
  return res;
}

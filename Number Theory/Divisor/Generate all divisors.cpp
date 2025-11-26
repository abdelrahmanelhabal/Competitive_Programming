int const N = 1e5 ;
vector<int> divs[N+1];
void generate() { 
  for (int i = 1; i <=N; i++) {
    for (int j = i ;  j<=N ; j+=i){
      divs[j].emplace_back(i);
    }
  }
}

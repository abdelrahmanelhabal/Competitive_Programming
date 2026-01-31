vector<int> KMP(string&s) {
  int n = s.size();
  vector<int>pi(n,0);
  int j = 0 ;
  for (int i = 1 ; i < n ; i++) {
    j = pi[i-1];
    while (j && s[j]!=s[i]) j = pi[j-1];
    if (s[i] == s[j])j++;
    pi[i] = j ;
  }
  return pi;
}
vector<vector<int>> automaton(string &s) {
  int m = s.size();
  vector<int> pi = KMP(s);

  vector<vector<int>> aut(m + 1, vector<int>(26));

  for (int i = 0; i <= m; i++) {
    for (int c = 0; c < 26; c++) {
      if (i < m && c == s[i] - 'a') {
        aut[i][c] = i + 1;
      }
      else {
        if (i == 0) aut[i][c] = 0;
        else aut[i][c] = aut[pi[i - 1]][c];
      }
    }
  }

  return aut;
}

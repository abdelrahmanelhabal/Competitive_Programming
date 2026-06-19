struct SAM {
  struct state {
      int len, link, first_pos;
      bool is_clone;
      int nxt[26];
  };

  static const int MAXN = 1e6 + 9;
  state st[2 * MAXN];
  int sz, last;
  int cnt[2 * MAXN] , vis[2 * MAXN];
  
  void sa_init() {
      st[0].len = 0;
      st[0].link = -1;
      fill(st[0].nxt, st[0].nxt + 26, -1);
  
      for (int i = 0; i < sz; ++i) {
          cnt[i] = 0;
          // is_terminal[i] = 0;
      }
  
      sz = 1;
      last = 0;
  }
  
  void sa_extend(char c, int pos) {
      int cur = sz++;
      st[cur].len = st[last].len + 1;
      st[cur].first_pos = pos;
      st[cur].is_clone = false;
      fill(st[cur].nxt, st[cur].nxt + 26, -1);
  
      cnt[cur] = 1;
      // is_terminal[cur] = 1;
      // pos_state[pos] = cur;
  
      int p = last, letter = c - 'a';
      while (p != -1 && st[p].nxt[letter] == -1) {
          st[p].nxt[letter] = cur;
          p = st[p].link;
      }
  
      if (p == -1) {
          st[cur].link = 0;
      } else {
          int q = st[p].nxt[letter];
          if (st[p].len + 1 == st[q].len) {
              st[cur].link = q;
          } else {
              int clone = sz++;
              st[clone].len = st[p].len + 1;
              copy(st[q].nxt, st[q].nxt + 26, st[clone].nxt);
              st[clone].link = st[q].link;
              st[clone].first_pos = st[q].first_pos;
              st[clone].is_clone = true;
  
              while (p != -1 && st[p].nxt[letter] == q) {
                  st[p].nxt[letter] = clone;
                  p = st[p].link;
              }
              st[q].link = st[cur].link = clone;
          }
      }
      last = cur;
  }
  
  void build(const string &s) {
      sa_init();
      for (int i = 0; i < (int) s.size(); i++) {
          sa_extend(s[i], i);
      }
  }

} suf;

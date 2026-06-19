int go(int cur) {
    int &ret = dp[cur];
    if (~ret) return ret;
    ret = 1 ; 
    for (int i = 0; i < 26; i++) {
        if (st[cur].nxt[i] != -1) {
            ret += go(st[cur].nxt[i]);
        }
    }
    return ret ;
}

string res;

void build(int cur, int rem) {
    if (rem <= 0) return;
    for (int i = 0; i < 26; i++) {
        int u = st[cur].nxt[i];
        if (u == -1) continue;
        int cnt = go(u);
        if (cnt >= rem) {
            res += char('a' + i);
            build(u, rem - 1);
            return;
        }
        rem -= cnt;
    }
}

string get(int k) {
    int all = go(0) - 1;
    assert(all >= k);
    build(0, k);
    return res;
}

int go(int v) {
    int &ret = dp[v] ; 
    if(~ret) return ret;
    ret = 0 ; 
    for (int c = 0; c < 26; c++) {
        int u = st[v].nxt[c];
        if (u != -1) {
            ret += cnt[u]; 
            ret += solve(u); 
        }
    }
    return ret;
}

void Kth(int k , int v = 0) {
    for (char c = 'a'; c <= 'z'; c++) {
        int u = st[v].nxt[c - 'a'];
        if (u == -1) continue;
        int total = cnt[u] + go(u);
        if (k <= total) {
            cout << c;
            if (k <= cnt[u]) return; 
            Kth(k - cnt[u] , u);
            return;
        } else {
            k -= total;
        }
    }
}

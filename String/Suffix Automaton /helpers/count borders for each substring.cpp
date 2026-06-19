int count_borders(string &s) {
    build(s);
    propagation();
    int res = 0;
    for (int i = 1; i < sz; i++) {
        int lg = st[i].len;
        int sh = st[st[i].link].len + 1;
        res += (cnt[i] * (cnt[i] + 1) / 2) * (lg - sh + 1);
    }
    return res;
}

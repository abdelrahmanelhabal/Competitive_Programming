int cmp(const string& t, int mid) const {
        int i = sa[mid], j = 0;
        while (i < n && j < (int)t.size()) {
            if (s[i] == t[j]) { i++; j++; }
            else return s[i] < t[j] ? 2 : 1;
        }
        return j == (int)t.size() ? 0 : 2; 
}
int countSubstring(const string& t) const {
    int l = 1, r = n, pos = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        int c = cmp(t, mid);
        if (c == 0) { pos = mid; break; }
        else if (c == 2) l = mid + 1;
        else r = mid - 1;
    }
    if (pos == -1) return 0;

    int tlen = t.size(), cnt = 1;
    for (int i = pos - 1; i >= 1 && lcp[i] >= tlen; i--) cnt++;

    for (int i = pos + 1; i <= n && lcp[i - 1] >= tlen; i++) cnt++;

    return cnt;
}
    
    
    
string kthSubstring(int k) const {
    for (int i = 1; i <= n; i++) {
        int prev_lcp = (i == 1) ? 0 : lcp[i - 1]; 
        int contrib = (n - sa[i]) - prev_lcp;

        if (k <= contrib) {
            return s.substr(sa[i], prev_lcp + k);
        }
        k -= contrib;
    }
    return ""; 
}    

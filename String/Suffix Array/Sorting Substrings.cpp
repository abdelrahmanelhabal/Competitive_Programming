struct SuffixArray {
    int n;
    string s;
    vector<int> sa;
    vector<int> lcp;
    vector<vector<int>> sparse;
 
    SuffixArray(string& str) : n(str.size()), s(str) {
        build();
        kasai();
        buildSparse();
    }
 
    void build() {
        s += char(0);
        int N = n + 1;
        vector<int> p(N), c(N), c1(N), cnt(max(256ll, (long long)N)), p1(N);
 
        for (int i = 0; i < N; i++) p[i] = i, c[i] = (unsigned char)s[i];
 
        for (int k = 0; (1 << k) < N; k++) {
            int len = 1 << k;
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < N; i++) cnt[c[min(N - 1, p[i] + len)]]++;
            for (int i = 1; i < (int)cnt.size(); i++) cnt[i] += cnt[i - 1];
            for (int i = N - 1; i >= 0; i--) p1[--cnt[c[min(N - 1, p[i] + len)]]] = p[i];
 
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < N; i++) cnt[c[p1[i]]]++;
            for (int i = 1; i < (int)cnt.size(); i++) cnt[i] += cnt[i - 1];
            for (int i = N - 1; i >= 0; i--) p[--cnt[c[p1[i]]]] = p1[i];
 
            c1[p[0]] = 0;
            for (int i = 1; i < N; i++)
                c1[p[i]] = c1[p[i - 1]] + (c[p[i]] != c[p[i - 1]] || c[min(N - 1, p[i] + len)] != c[min(N - 1, p[i - 1] + len)]);
            c.swap(c1);
 
            if (c[p[N - 1]] == N - 1) break;
        }
 
        sa = p;
        s.pop_back();
    }
 
    void kasai() {
        int N = n + 1;
        vector<int> rank(N, 0);
        for (int i = 0; i < N; i++) rank[sa[i]] = i;
 
        lcp.assign(n, 0);
        int k = 0;
        for (int i = 0; i <= n; i++) {
            if (rank[i] == N - 1) {
                k = 0;
                continue;
            }
            int j = sa[rank[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
            lcp[rank[i]] = k;
            if (k) k--;
        }
    }
 
    void buildSparse() {
        int m = lcp.size();
        int LOG = 1;
        while ((1 << LOG) <= m) LOG++;
        sparse.assign(LOG, vector<int>(m, 0));
        sparse[0] = lcp;
        for (int j = 1; j < LOG; j++)
            for (int i = 0; i + (1 << j) <= m; i++)
                sparse[j][i] = min(sparse[j-1][i], sparse[j-1][i + (1 << (j-1))]);
    }
 
    int queryLCP(int l, int r) {
        if (l > r) return 0;
        int k = __lg(r - l + 1);
        return min(sparse[k][l], sparse[k][r - (1 << k) + 1]);
    }
 
    vector<int> getRank() {
        vector<int> rank(n + 1);
        for (int i = 0; i <= n; i++) rank[sa[i]] = i;
        return rank;
    }
 
    int lcpOf(int a, int b, const vector<int>& rank) {
        if (a == b) return n - a;
        int ra = rank[a], rb = rank[b];
        if (ra > rb) swap(ra, rb);
        return queryLCP(ra, rb - 1);
    }
 
     int cmpSubstr(int l1, int r1, int l2, int r2, const vector<int>& rank) {
        int len1 = r1 - l1 + 1, len2 = r2 - l2 + 1;
        int common = lcpOf(l1, l2, rank);
        int minLen = min(len1, len2);
        if (common >= minLen) {
            if (len1 == len2) return 0;
            return len1 < len2 ? -1 : 1;
        }
          return rank[l1 + common] < rank[l2 + common] ? -1 : 1;
    }
};
 
void solve() {
    string s; cin >> s;
    int n = s.size();
 
    SuffixArray sa(s);
    vector<int> rank = sa.getRank();
 
    int q; cin >> q;
    vector<pair<int,int>> queries(q);
    for (auto& [l, r] : queries) {
        cin >> l >> r;
        l--; r--; 
    }
 
    vector<int> idx(q);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        auto [l1, r1] = queries[i];
        auto [l2, r2] = queries[j];
        int cmp = sa.cmpSubstr(l1, r1, l2, r2, rank);
        if (cmp != 0) return cmp < 0;
        if (l1 != l2) return l1 < l2;
        return r1 < r2;
    });
 
    for (int i : idx) {
        cout << queries[i].first + 1 << " " << queries[i].second + 1 << "\n";
    }
}

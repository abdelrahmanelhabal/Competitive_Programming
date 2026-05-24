struct SuffixArray {
    int n;
    string s;
    vector<int> sa;  
    vector<int> lcp; 
 
    SuffixArray(string& str) : n(str.size()), s(str) {
        build();
        kasai();
    }
 
    void build() {
        s += char(0);
        int N = n + 1; 
        vector<int> p(N), c(N), c1(N), cnt(max(256ll, N)), p1(N);
 
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
    
};

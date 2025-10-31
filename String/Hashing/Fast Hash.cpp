struct FastHash {
    static constexpr unsigned int B = 1315423911ULL;
    vector<unsigned int> pre, suf, pw;
    int n;
    FastHash(const string &s) {
        n = s.size();
        pre.resize(n+1);
        suf.resize(n+2);
        pw .resize(n+1);
        pre[0] = 0;
        pw [0] = 1;
        for(int i = 0; i < n; i++){
            pre[i+1] = pre[i]*B + (unsigned char)s[i];
            pw [i+1] = pw [i] * B;
        }
        // build reverse-direction suffix‐hash
        suf[n]   = 0;
        for(int i = n-1; i >= 0; i--){
            suf[i] = suf[i+1]*B + (unsigned char)s[i];
        }
    }
    // forward hash of s[L..R]
    inline unsigned int fwd(int L, int R) const {
        // h[R+1] - h[L]*B^(R-L+1)
        return pre[R+1] - pre[L]*pw[R-L+1];
    }
    // reverse‐direction hash of s[L..R]
    inline unsigned int rev(int L, int R) const {
        // suf[L] - suf[R+1]*B^(R-L+1)
        return suf[L]   - suf[R+1]*pw[R-L+1];
    }
};


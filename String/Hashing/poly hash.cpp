int const N = 1e5+1;
const uint64_t HashMod = (1ULL << 61) - 1;
const uint64_t seed = chrono::system_clock::now().time_since_epoch().count();
const uint64_t base = mt19937_64(seed)() % (HashMod / 3) + (HashMod / 3);
uint64_t power[N];

int64_t MUL(uint64_t a, uint64_t b) {
    uint64_t l1 = (uint32_t) a, h1 = a >> 32, l2 = (uint32_t) b, h2 = b >> 32;
    uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    uint64_t ret = (l & HashMod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & HashMod) + (ret >> 61);
    ret = (ret & HashMod) + (ret >> 61);
    return (int64_t) ret - 1;
}
void init() {
    power[0] = 1;
    for (int i = 1; i < N; i++) {
        power[i] = MUL(power[i - 1], base);
    }
}
struct Hash{
    vector<int64_t> pre,suf ;
    template<typename T>
    Hash(const vector<T>&a) {
        int n = a.size();
        pre.resize(n+4,0);
        suf.resize(n+4,0);
        for (int i = 1 ; i<=n ; i++) {
            pre[i] = MUL(pre[i-1],base) + a[i-1] + 997 ;
            if (pre[i] >= HashMod) pre[i]-=HashMod;
        }
        for (int i = n ; i >= 1; i--) {
            suf[i] = MUL(suf[i+1],base) + a[i-1] + 997;
            if (suf[i] >= HashMod) pre[i]-=HashMod;
        }
    }
    explicit Hash(string str) 
    : Hash(vector<char>(str.begin(), str.end())) {}
    uint64_t get_hash(int l, int r) {
        int64_t h = pre[r + 1] - MUL(power[r - l + 1], pre[l]);
        return h < 0 ? h + HashMod : h;
    }

    uint64_t rev_hash(int l, int r) {
        int64_t h = suf[l + 1] - MUL(power[r - l + 1], suf[r + 2]);
        return h < 0 ? h + HashMod : h;
    }
};

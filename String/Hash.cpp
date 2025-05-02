const uint64_t mod = (1ULL << 61) - 1; // 2^61 - 1
const uint64_t seed = chrono::system_clock::now().time_since_epoch().count();
const uint64_t base = mt19937_64(seed)() % (mod / 3) + (mod / 3);
const int N = 1e5 + 5;

uint64_t power[N];

// Safe modular multiplication function
int64_t MUL(uint64_t a, uint64_t b) {
    uint64_t l1 = (uint32_t) a, h1 = a >> 32, l2 = (uint32_t) b, h2 = b >> 32;
    uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    uint64_t ret = (l & mod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & mod) + (ret >> 61);
    ret = (ret & mod) + (ret >> 61);
    return (int64_t) ret - 1;
}

// Precompute powers of the base
void pre() {
    power[0] = 1;
    for (int i = 1; i < N; i++) {
        power[i] = MUL(power[i - 1], base);
    }
}

struct Hash {
    vector<int64_t> prefix , suffix ; // Prefix and suffix hashes
    str s;

    template<typename T>
    Hash(const vector<T> &s) {
        if (!power[0]) pre(); // Initialize base powers if not already done

        int n = s.size();
        assert(n < N); // Ensure the size is within bounds
        prefix.resize(n + 3, 0), suffix.resize(n + 3, 0);

        // Compute prefix hashes
        for (ll i = 1; i <= n; i++) {
            prefix[i] = MUL(prefix[i - 1], base) + s[i - 1];
            if (prefix[i] >= mod) prefix[i] -= mod;
        }

        // Compute suffix hashes
        for (ll i = n; i >= 1; i--) {
            suffix[i] = MUL(suffix[i + 1], base) + s[i - 1];
            if (suffix[i] >= mod) suffix[i] -= mod;
        }
    }

    // Update the hash after a character change
    void update(ll pos, char ch) {
        ll n = s.size();
        s[pos] = ch;

        // Recompute prefix hashes from pos to end
        for (ll i = pos + 1; i <= n; i++) {
            prefix[i] = MUL(prefix[i - 1], base) + s[i - 1];
            if (prefix[i] >= mod) prefix[i] -= mod;
        }

        // Recompute suffix hashes from pos to start
        for (ll i = pos + 1; i >= 1; i--) {
            suffix[i] = MUL(suffix[i + 1], base) + s[i - 1];
            if (suffix[i] >= mod) suffix[i] -= mod;
        }
    }

    // Get hash for substring [l, r] (0-based indexing)
    uint64_t get_hash(ll l , ll r) {
        int64_t h = prefix[r + 1] - MUL(power[r - l + 1], prefix[l]);
        return h < 0 ? h + mod : h;
    }

    // Get reverse hash for substring [l, r] (0-based indexing)
    uint64_t rev_hash(ll l, ll r) {
        int64_t h = suffix[l + 1] - MUL(power[r - l + 1], suffix[r + 2]);
        return h < 0 ? h + mod : h;
    }
};
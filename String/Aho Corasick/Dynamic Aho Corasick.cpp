struct static_Aho {

    enum { alpha = 26, first = 'a' };

    struct Node {
        int nxt[alpha];
        int suflink = 0;
        int start = -1;
        int end = -1;
        int nmatches = 0;
        int lvl = 0;

        Node(int v) {
            memset(nxt, v, sizeof nxt);
        }
    };

    vector<Node> v;
    vector<int> backup;
    void insert(string &s, int id) {
        int node = 0;
        int clvl = 0;
        for (auto &c: s) {
            int &m = v[node].nxt[c - first];

            ++clvl;
            if (m == -1) {
                node = m = v.size();
                v.emplace_back(-1);
                v.back().lvl = clvl;
            } else node = m;
        }
        if (v[node].end == -1) v[node].start = id;
        backup.emplace_back(v[node].end);
        v[node].end = id;
        v[node].nmatches++;
    }

    static_Aho(vector<string> &pat) : v(1, -1) {
        for (int i = 0; i < pat.size(); ++i)
            insert(pat[i], i);
        v[0].suflink = v.size();
        v.emplace_back(0);
        queue<int> q;
        q.push(0);
        while (q.size()) {
            int node = q.front();
            q.pop();
            int prv = v[node].suflink;

            for (int i = 0; i < alpha; ++i) {
                int &x = v[node].nxt[i], y = v[prv].nxt[i];
                if (x == -1) x = y;
                else {
                    v[x].suflink = y;
                    (v[x].end == -1 ? v[x].end : backup[v[x].start]) = v[y].end;
                    v[x].nmatches += v[y].nmatches;
                    q.push(x);
                }
            }
        }
    }

    void clear() {
        v.clear();
        backup.clear();
    }
};

struct dynamic_Aho {
    vector<string> li[20];
    static_Aho *ac[20];

    vector<string> rli[20];
    static_Aho *rac[20];

    dynamic_Aho() {
        for (int i = 0; i < 20; ++i) ac[i] = nullptr, rac[i] = nullptr;
    }

    void clear() {
        for (int i = 0; i < 20; ++i) {
            li[i].clear();
            rli[i].clear();
            if (ac[i]) {
                delete ac[i];
                ac[i] = nullptr;
            }
            if (rac[i]) {
                delete rac[i];
                rac[i] = nullptr;
            }
        }
    }

    ~dynamic_Aho() {
        clear();
    }

    void add_word(const string &s) {
        int pos = 0;
        while (pos < 20 && !li[pos].empty()) ++pos;
        if (pos == 20) pos = 19;

        li[pos].push_back(s);

        for (int bef = 0; bef < pos; ++bef) {
            if (li[bef].empty()) continue;
            li[pos].insert(li[pos].end(), li[bef].begin(), li[bef].end());
            li[bef].clear();
            if (ac[bef]) {
                delete ac[bef];
                ac[bef] = nullptr;
            }
        }

        if (ac[pos]) {
            delete ac[pos];
            ac[pos] = nullptr;
        }
        ac[pos] = new static_Aho(li[pos]);
    }

    void remove(const string &s) {
        int pos = 0;
        while (pos < 20 && !rli[pos].empty()) ++pos;
        if (pos == 20) pos = 19;

        rli[pos].push_back(s);

        for (int bef = 0; bef < pos; ++bef) {
            if (rli[bef].empty()) continue;
            rli[pos].insert(rli[pos].end(), rli[bef].begin(), rli[bef].end());
            rli[bef].clear();
            if (rac[bef]) {
                delete rac[bef];
                rac[bef] = nullptr;
            }
        }

        if (rac[pos]) {
            delete rac[pos];
            rac[pos] = nullptr;
        }
        rac[pos] = new static_Aho(rli[pos]);
    }

    static long long get_count_single(static_Aho *acptr, const string &s) {
        if (!acptr) return 0;
        long long ans = 0;
        int node = 0;
        for (char ch: s) {
            int idx = ch - static_Aho::first;
            if (idx < 0 || idx >= (int) static_Aho::alpha) {
                node = 0;
                continue;
            }
            node = acptr->v[node].nxt[idx];
            ans += acptr->v[node].nmatches;
        }
        return ans;
    }

    int get_count(const string &s) {
        long long ans = 0;
        for (int l = 0; l < 20; ++l) {
            if (ac[l]) ans += get_count_single(ac[l], s);
            if (rac[l]) ans -= get_count_single(rac[l], s);
        }
        if (ans < 0) ans = 0;
        return (int) ans;
    }
};


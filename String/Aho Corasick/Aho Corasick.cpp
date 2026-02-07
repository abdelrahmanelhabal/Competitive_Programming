struct AC {
    int N ;
    const int A = 26;
    vector <vector <int>> next;
    vector <int> link, out_link;
    vector <vector <int>> out;
    AC(): N(0) {
        node();
    }
    int node() {
        next.emplace_back(A, 0);
        link.emplace_back(0);
        out_link.emplace_back(0);
        out.emplace_back(0);
        return N++;
    }
    inline int get (char c) {
        return c - 'a';
    }
    void add_pattern (const string T, int idx) {
        int u = 0;
        for (auto c : T) {
            if (!next[u][get(c)]) next[u][get(c)] = node();
            u = next[u][get(c)];
        }
        out[u].push_back(idx);
    }
    void compute() {
        queue<int> q;
        for (int c = 0; c < A; ++c)
            if (next[0][c]) q.push(next[0][c]);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int c = 0; c < A; ++c) {
                int v = next[u][c];
                if (!v) next[u][c] = next[link[u]][c];
                else {
                    link[v] = next[link[u]][c];
                    out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
                    q.push(v);
                }
            }
        }
    }
    int advance (int u, char c) {
        while (u && !next[u][get(c)]) u = link[u];
        u = next[u][get(c)];
        return u;
    }
};

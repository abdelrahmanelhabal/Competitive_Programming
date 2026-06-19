array<int, 4> get_lcs(const string &t) {
    int cur_len = 0, node = 0;
    pair<int, int> bst{0, -1}; // {length, end_index_in_t}
    int best_node = 0;

    for (int i = 0; i < (int) t.size(); ++i) {
        int ch = t[i] - 'a';

        while (node != -1 && st[node].nxt[ch] == -1) {
            node = st[node].link;
            if (node != -1) cur_len = st[node].len;
        }

        if (node == -1) {
            node = 0;
            cur_len = 0;
            continue;
        }

        node = st[node].nxt[ch];
        ++cur_len;

        if (cur_len > bst.first) {
            bst = {cur_len, i};
            best_node = node;
        }
    }

    if (bst.first == 0) return {-1, -1, -1, -1}; // no common substring

    int len = bst.first;
    int ed_t = bst.second;
    int st_t = ed_t - len + 1;

    int ed_s = st[best_node].first_pos;
    int st_s = ed_s - len + 1;

    return {st_s, ed_s, st_t, ed_t};
}

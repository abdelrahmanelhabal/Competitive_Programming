// Count distinct rotations of string t in SAM
int count_rotations(const string &t) {
    int n = (int)t.size();
    if (n == 0) return 0;

    string s = t + t;
    s.pop_back();

    int node = 0;
    int cur_len = 0;

    int ans = 0;
    vector<int> reset;

    for (int i = 0; i < (int)s.size(); i++) {
        int ch = s[i] - 'a';

        while (node != -1 && st[node].nxt[ch] == -1) {
            node = st[node].link;

            if (node != -1)
                cur_len = st[node].len;
            else
                cur_len = 0;
        }

        if (node == -1)
            break;

        node = st[node].nxt[ch];
        ++cur_len;

        if (cur_len < n)
            continue;

        while (st[node].link != -1 &&
               st[st[node].link].len >= n) {
            node = st[node].link;
        }

        if (!vis[node]) {
            vis[node] = true;
            ans += cnt[node];
            reset.push_back(node);
        }
    }

    for (int v : reset)
        vis[v] = false;

    return ans;
}


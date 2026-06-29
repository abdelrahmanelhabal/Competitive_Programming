map<vector<int>, int> mp;

void tree_hash(int u, int p, vector<int> &hash, vector<vector<int>> adj) {
    vector<int> child;
    for (auto &v : adj[u]) {
        if (v != p) {
            tree_hash(v, u, hash, adj);
            child.emplace_back(hash[v]);
        }
    }

    // Uncomment the following line if the order of children doesn't matter
    // sort(child.begin(), child.end());

    if (!mp.count(child)) {
        mp[child] = mp.size() + 1;
    }
    hash[u] = mp[child];
}

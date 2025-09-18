const int INF = 1e9;
int n;
vector<vector<pair<int,int>>> adj; // {weight, neighbor}
void prim() {
    vector<int> min_w(n, INF), parent(n, -1);
    vector<bool> inMST(n, false);
    set<pair<int,int>> q; // {weight, node}

    min_w[0] = 0;
    q.insert({0, 0});

    int total_weight = 0;

    for (int i = 0; i < n; i++) {
        if (q.empty()) {
            cout << "No MST!" << endl ;
            return;
        }
        auto [w, v] = *q.begin();
        q.erase(q.begin());

        if (inMST[v]) continue; // skip outdated entries
        inMST[v] = true;
        total_weight += w;

        if (parent[v] != -1)
            cout << parent[v] << " -> " << v << "\n";

        for (auto [edge_w, to] : adj[v]) {
            if (!inMST[to] && edge_w < min_w[to]) {
                q.erase({min_w[to], to}); // remove old entry if exists
                min_w[to] = edge_w;
                parent[to] = v;
                q.insert({edge_w, to});
            }
        }
    }
    cout << "Total weight = " << total_weight << "\n";
}

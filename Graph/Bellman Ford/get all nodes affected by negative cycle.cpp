int n , m ; cin >> n >> m ;
    vector<tuple<int,int,int>>edge(m);
    vector<vector<int>>adj(n);
    for (auto &[u,v,w] : edge) {
        cin >>u >> v >> w ;
        u--,v--;
        adj[u].emplace_back(v);
        w = -w;
    }
    vector<int>dis(n,1e18);
    dis[0] = 0 ;
    for (int i = 0 ; i< n ; i++) {
        for (auto [u,v,w] : edge) {
            if (dis[u] != 1e18) {
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w ;
                }
            }
        }
    }
    auto ref = dis;
    for (int i = 0 ; i< n ; i++) {
        for (auto [u,v,w] : edge) {
            if (dis[u] != 1e18) {
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w ;
                }
            }
        }
    }
    queue<int> q;
    vector<int>cycle(n,false);
    for (int i = 0 ; i< n ; i++) {
        if (dis[i] != ref[i]) {
            cycle[i] = 1;
            q.emplace(i);
        }
    }
    while (q.size()) {
        auto u = q.front(); q.pop();
        for (auto v : adj[u]) {
            if (!cycle[v]) {
                cycle[v] = 1;
                q.emplace(v);
            }
        }
    }
    for (int i = 0 ; i < n ; i++) {
        if (cycle[i]) {
            cout << i+1 << " "; 
        }
        cout << endl ;
    }

int n , m ; cin >> n >> m ;
    vector<tuple<int,int,int>>edge(m);
    for (auto &[u,v,w] : edge) {
        cin >> u >> v >> w ;
        u--,v--;
    }
    vector<int>dis(n,1e18) , prev(n,-1);
    int cyclic_node = -1 ;
    for (int i = 0 ; i< n ; i++) {
        for (auto [u,v,w] : edge) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w ;
                prev[v] = u ;
                if (i == n-1) {
                    cyclic_node = v ;
                }
            }
        }
    }
    if (cyclic_node == -1) {
        cout << "NO" << endl ;
    }
    else {
        cout << "YES" << endl ;
        for (int i = 0 ; i < n ; i++) {
            cyclic_node = prev[cyclic_node] ;
        }
        vector<int>path;
        for (int i = cyclic_node ; (i != cyclic_node || path.empty())  ; i = prev[i]) {
            path.emplace_back(i) ;
        }
        path.emplace_back(cyclic_node) ;
        reverse(all(path));
        for (auto i : path) {
            cout << i+1 << " ";
        }
        cout << endl ;
    }

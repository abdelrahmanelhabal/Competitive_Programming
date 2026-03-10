int n , m ; cin >> n >> m ;
    vector<tuple<int,int,int>>edge(m);
    for (auto &[u,v,w]:edge) {
        cin >> u >> v >> w ;
        u--,v--;
    }
    vector<int>dis(n,1e18),prev(n,-1);
    dis[0] = 0 ;
    bool cycle = false;
    for (int i = 0 ; i< n ; i ++) {
        for (auto[u,v,w] : edge) {
            if (dis[u]!=1e18) {
               if (dis[v] > dis[u]+w) {
                   dis[v] = dis[u]+w;
                   prev[v] = u ;
                   cycle |= (i == n-1);
               }
            }
        }
    }
    vector<int>path;
    int target = n-1 ;
    while (target!=-1) {
        path.emplace_back(target);
        target = prev[target];
    }
    reverse(all(path));
    for (auto i : path) {
        cout << i << " " ;
    }
    cout << endl ;

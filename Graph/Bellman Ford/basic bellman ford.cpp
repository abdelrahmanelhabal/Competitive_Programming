int const INF =1e18;
int n , m ; cin >> n >> m ;
    vector<tuple<int,int,int>>edge(m);
    for (auto &[u,v,w] : edge) {
        cin >> u >> v >> w ;
        u--,v--;
    }
    int source ; cin >> source;
    source--;
    vector<int>dis(n,INF);
    dis[source] = 0 ;
    for (int i = 0 ; i < n -1 ; i++) {
        for (auto [u,v,w]:edge) {
            if (dis[u]!=1e18) {
                dis[v] = min(dis[v],dis[u]+w);
            }
        }
    }

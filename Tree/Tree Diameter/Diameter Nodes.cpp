int diameter(int start ,int n, vector<int>&dis,vector<vector<int>>&adj) {
    dis.assign(n+1,-1);
    queue<int> q;
    q.emplace(start);
    dis[start] = 0;
    while(!q.empty()) {
        auto node = q.front();  q.pop();
        for (auto child : adj[node]) {
            if (dis[child]==-1) {
                dis[child] = dis[node] + 1;
                q.emplace(child);
            }
        }
    }
    int node = 1 ; 
    for(int i = 2 ; i <= n ; i++){
        if(dis[i] > dis[node]){node=i;}
    }
    return node;
}
void solve() {
    int n ; cin >> n ;
    vector<vector<int>>adj(n+1);
    for (int i = 1; i < n ; i++) {
        int u , v ; cin >> u >> v ;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<int>dis1(n+1,-1),dis2(n+1,-1);
    int u = diameter(1,n,dis1,adj);
    int v = diameter(u,n,dis1,adj);
    diameter(v,n,dis2,adj);
    cout << u << " " << v << endl ;
}

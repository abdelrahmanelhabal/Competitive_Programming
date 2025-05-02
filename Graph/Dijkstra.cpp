/*
    Find Shortest path from Single Sourse to other vertices in O(n log(n))
    Dijkstra can used if weight of edge >= 0
*/
void Dijkstra(){
    int n , m; cin >> n >> m ;
vector<pair<ll,ll>> adj[n+1]; // 1-base
for(int i = 0 ; i < m ; i++){
    ll  u , v ,w; cin >> u >> v >> w;
    adj[u].emplace_back(v , w);
    adj[v].emplace_back(u , w);
}
int Start ; cin >> Start;
priority_queue<pair<ll,ll>, vector<pair<ll,ll>> , greater<>> q;
vector<ll> dis(n+1, INF);
q.emplace(0 , Start);
dis[Start] = 0;
while(!q.empty()){
    auto [w,node] = q.top(); q.pop();
    if (dis[node] < w){continue;}
    for (auto [child , weight] : adj[node]) {
        if (dis[child] > dis[node]+weight) {
            dis[child] = dis[node]+weight;
            q.emplace(dis[child],child);
        }
    }
}
for (int i = 1; i <=n ; i++) {
    cout << "Shortest path form node " << Start <<  " to node " << i << " is : "  << dis[i] << endl;
}
}
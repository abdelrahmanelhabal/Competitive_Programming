/*
Find the shortest path from a source to other vertices in an unweighted graph in o(n+m)
*/
void bfs(vector<vector<ll>>&adj , vector<ll>&dis) {
    queue<ll> q;
    q.push(1);
    dis[1]=0;
    while(!q.empty()) {
        ll node = q.front();
        q.pop();
        for (auto child : adj[node]) {
            if (dis[child] == -1) {
                dis[child] = dis[node] + 1;
                q.push(child);
            }
        }
    }
}
void solve() {
    ll n , m ; cin >> n >> m ;
    vector<vector<ll>>adj(n+1); // 1-base
    for (int i = 0 ; i < m ; i++) {
        ll from , to ; cin >> from>> to;
        adj[from].push_back(to);
        adj[to].push_back(from);
    }
    vector<ll> dis(n+1,-1);
    bfs(adj,dis);
    for (int i = 1 ; i <=n ; i++) {
        cout << dis[i] << ' ' ;
    }
    cout << endl ;
}
int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int tc = one; //cin >> tc;
    while (tc--) { solve(); }
    return 0;
}

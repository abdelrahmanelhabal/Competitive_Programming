#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define ll long long
#define ld long double
#define endl '\n'
void dfs(int node , vector<vector<int>>&adj , vector<int>&vis) {
    vis[node]=1;
    for (auto child : adj[node]) {
        if (!vis[child]) dfs(child,adj,vis);
    }
}
void solve() {
int n , m ; cin >> n >> m ;
    vector<vector<int>> adj(n); // 0-base
    for (int i = 0 ; i < m ; i++) {
        int u , v ; cin >> u >> v ;
        u--,v--;
        adj[u].emplace_back(v) ;
        adj[v].emplace_back(u) ;
    }
    vector<int>cities , vis(n,0);
    for (int i = 0 ; i < n ; i++) {
        if (!vis[i]) {
            dfs(i,adj,vis);
            cities.emplace_back(i);
        }
    }
    cout << cities.size()-1 << endl ;
    for (int i = 0 ; i < cities.size()-1 ; i++) {
        cout << cities[i]+1 << " " << cities[i+1]+1 << endl ;
    }
}
int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int tc = 1; //cin >> tc;
    while (tc--) { solve(); }
    return 0;
}

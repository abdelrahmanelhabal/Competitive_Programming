#include <bits/stdc++.h>
using namespace std;
#define ll long long

/*Find all connected components in an undirected graph in O(n + m) time: */

void dfs(int node , vector<vector<int>>&adj, vector<int>&vis) {
    vis[node]=1;
    for (auto child : adj[node]) {
        if (!vis[child]) {
            dfs(child,adj,vis);
        }
    }
}
int main(){
    int n, m; cin >> n >> m; // Number of vertices and edges

    vector<vector<int>> adj(n+1); // 1-base

    // Read in the graph
    for (int i = 0; i < m; ++i) {
        int from, to; cin >> from >> to;
        adj[to].push_back(from);
        adj[from].push_back(to);
    }

    vector<int> vis(n+1, 0);
    int componentCount = 0;

    for (int i = 1; i <=n; ++i) {
        if (!vis[i]) {
            componentCount++;
            dfs(i,adj,vis);
        }
    }
    cout << "Number of connected components: " << componentCount << endl;
}
// solve this https://cses.fi/problemset/task/1192
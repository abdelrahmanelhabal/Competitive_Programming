#include <bits/stdc++.h>
using namespace std;
#define ll long long
bool dfs(int node , vector<vector<int>>&adj , vector<int>&color) {
    bool Bipartite = true;
    for (auto child : adj[node]) {
        if (color[child] == -1) {
           if (color[node]==1) { color[child]=0; }
           else { color[child]=1; }

           Bipartite&=dfs(child,adj,color);
        }
        else {
            if (color[node]==color[child]) {
                Bipartite=false;
            }
        }
    }
    return Bipartite;
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

    vector<int>color(n+1,-1);
    bool Bipartite  = true;
    for (int i = 1; i <=n; ++i) {
        if (color[i]==-1) {
            color[i]=1;
            Bipartite&=dfs(i,adj,color);
        }
    }

    if (Bipartite){cout << "YES" << endl;}
    else{cout << "NO" << endl ;}

}
// solve this  https://cses.fi/problemset/task/1668/
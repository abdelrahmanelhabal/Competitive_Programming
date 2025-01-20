#include <bits/stdc++.h>
using namespace std;
#define ll long long

/*Find all connected components in an undirected graph in  O(n + m)  time: */
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
            queue<int> q;
            q.push(i);
            vis[i] = 1;
            while (!q.empty()) {
                int node = q.front(); q.pop();

                for (int child : adj[node]) {
                    if (!vis[child]) {
                        vis[child] = 1;
                        q.push(child);
                    }
                }
            }
        }
    }
    cout << "Number of connected components: " << componentCount << endl;
}
// solve this Problem https://cses.fi/problemset/task/1192 
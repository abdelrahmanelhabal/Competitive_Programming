#include <bits/stdc++.h>
using namespace std;
#define ll long long
/* 
Finding the shortest cycle in a undirected unweighted graph: 
Start a BFS from each vertex. 
As soon as we try to go from the current vertex back to the source vertex, 
we have found the shortest cycle containing the source vertex. 
At this point we can stop the BFS, and start a new BFS from the next vertex. 
From all such cycles (at most one from each BFS) choose the shortest.
*/
int main(){
    int n, m; cin >> n >> m; 
    
    vector<vector<ll>> adj(n+1);

    for (int i = 0; i < m; ++i) {
        ll from , to; cin >> from >> to;
        adj[from].emplace_back(to);
        adj[to].emplace_back(from);
    }

    ll shortestCycle = 1e9;
    for (int i = 1 ; i <=n ;i++) {
        
        vector<ll> dist(n+1, -1);
        vector<ll> parent(n+1, -1);
        queue<ll> q;

        q.push(i);
        dist[i] = 0;

        while (!q.empty()) {
            ll node = q.front(); q.pop();

            for (auto child : adj[node]) {
                if (dist[child] == -1) {
                    dist[child] = dist[node] + 1;
                    parent[child] = node;
                    q.push(child);
                }
                else if (child != parent[node]) {
                    ll cycle = (dist[node] + dist[child] + 1);
                  shortestCycle  = min(shortestCycle,cycle);
                    break;
                }
            }
        }
    }
     
    if (shortestCycle == 1e9) {
        cout << -1 << endl ;
    }
    else {
        cout << shortestCycle << endl ;
    }
}

// solve this problem  https://cses.fi/problemset/task/1707
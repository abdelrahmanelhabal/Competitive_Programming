#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
ll diameter(ll start ,ll n, vector<ll>&dis,vector<vector<ll>>&adj) {
    dis.assign(n+1,-1);
    queue<ll> q;
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
    ll node = 1 ; 
    for(int i = 2 ; i <= n ; i++){
        if(dis[i] > dis[node]){node=i;}
    }
    return node;
}
void solve() {
    ll n ; cin >> n ;
    vector<vector<ll>>adj(n+1);
    for (int i = 1; i < n ; i++) {
        ll u , v ; cin >> u >> v ;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<ll>dis1(n+1,-1),dis2(n+1,-1);
    ll u = diameter(1,n,dis1,adj);
    ll v = diameter(u,n,dis1,adj);
    diameter(v,n,dis2,adj);
    cout << u << " " << v << endl ;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}

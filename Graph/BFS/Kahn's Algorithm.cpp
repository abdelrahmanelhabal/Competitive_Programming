#include <bits/stdc++.h>
using namespace std;
/* 
Find  lexicographically (largest Or smallest) topological sort 
*/
int main() {
ll n , m ; cin >> n >> m ;
    vector<vector<ll>>adj(n+1); // 1-base 
    vector<ll>inDeg(n+1,0);

    for (int i = 0 ; i< m ; i++) {
        ll from ,to ; cin >>from >> to ;
        adj[from].push_back(to) ;
        inDeg[to]++ ;
    }
    priority_queue<ll,vector<ll>,greater<ll>> q ;
    
    for (int i = 1; i <=n ;i++) {
        if (inDeg[i] == 0) {
           q.push(i) ;
        }
    }

    vector<ll> ans;
    while (!q.empty()) {
        ll node = q.top(); q.pop();
        ans.push_back(node);
        for (auto child : adj[node]) {
            inDeg[child]-- ;
            if (inDeg[child] == 0) {
                q.emplace(child) ;
            }
        }
    }
    if (ans.size()!=n){cout << "You can`t Sort" << endl ;return;}
    for (auto node: ans) {
        cout << node << " " ;
    }
    cout << endl ;
}

// solve this problem https://www.spoj.com/problems/TOPOSORT/ 
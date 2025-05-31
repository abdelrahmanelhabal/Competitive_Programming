#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'
struct UnDirectEulerCycle {
    vector<multiset<int>>adj;
    vector<int> deg , tour;
    int n , m ;
    UnDirectEulerCycle(int n , vector<pair<int,int>>&edge) {
        this-> n = n ;
        m = edge.size();
        deg.resize(n,0);
        adj.resize(n);
        for (auto &[u,v]:edge) {
            adj[u].emplace(v);
            adj[v].emplace(u);
            deg[u]++;
            deg[v]++;
        }
    }
    void dfs(int node) {
        while (!adj[node].empty()) {
            int child = *adj[node].begin();
            adj[node].erase(adj[node].begin());
            adj[child].erase(adj[child].find(node));
            dfs(child);
        }
        tour.emplace_back(node);
    }

    bool get() {
        for (int i = 0; i < n; ++i) {
            if (deg[i] % 2 != 0) {
                return false;
            }
        }
        dfs(0);
        reverse(all(tour));
        if (tour.size() != m+1) {
            return false;
        }
        return true;
    }
};
void solve() {
    int n , m ; cin >> n >> m ;
    vector<pair<int,int>>edge;
    for (int i = 0 ; i < m ; i++) {
        int u , v ; cin >> u >>  v;
        u--,v--;
        edge.emplace_back(u,v);
    }
    UnDirectEulerCycle d(n,edge);
    bool flag = d.get();
    if (flag) {
        vector<int> ans = d.tour;
        for (auto i : ans) {
            cout << i+1 << ' ';
        }
        cout << endl ;
    }
    else {
        cout << "IMPOSSIBLE" << endl ;
    }
}


signed main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int tc =1;  //cin >> tc ;
    while (tc--) solve();
    return 0;
}

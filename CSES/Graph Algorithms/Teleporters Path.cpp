#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'
struct DirectEulerPath {
    vector<vector<int>>adj;
    vector<int> in , out , tour;
    int n , s , e , m ;
    DirectEulerPath(int n , int start , int end , vector<pair<int,int>>&edge) {
        this-> n = n ;
        s = start , e = end ;
        m = edge.size();
        adj.resize(n);in.resize(n);out.resize(n);
        for (auto &[u,v]:edge) {
            adj[u].emplace_back(v);
            out[u]++;
            in[v]++;
        }
    }
    bool get() {
        for (int i = 0; i < n; ++i) {
            if (i == s) {
                if (out[i] != in[i] + 1) return false ;
            } else if (i == e) {
                if (in[i] != out[i] + 1) return false ;
            } else {
                if (in[i] != out[i]) return false ;
            }
        }
        dfs(s);
        reverse(all(tour));
        if ((int)tour.size() != m + 1 || tour.front() != s || tour.back() != e) {
           return false;
        }
        return true;
    }
    void dfs(int node) {
        while (out[node]) {
            out[node]--;
            int child = adj[node][out[node]];
            dfs(child);
        }
        tour.emplace_back(node);
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
    DirectEulerPath d(n,0,n-1,edge);
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

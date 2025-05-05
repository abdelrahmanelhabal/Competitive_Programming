#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define ll long long
#define ld long double
#define endl '\n'
int dx[] {1,-1,0,0};
int dy[] {0,0,1,-1};
int n , m ;
bool valid(int i , int j) {
    return i >=0 && i < n && j >= 0 && j < m ;
}
void dfs(int i, int j  , vector<vector<char>>&adj , vector<vector<int>>&vis) {
    vis[i][j]=1;
    for (int k = 0 ; k < 4 ; k++) {
        int ni = i + dx[k] , nj = j + dy[k] ;
        if (valid(ni,nj) && !vis[ni][nj] && adj[ni][nj]=='.') {
            dfs(ni,nj,adj,vis);
        }
    }
}
void solve() {
    cin >> n >> m ;
    vector<vector<char>>adj(n,vector<char>(m));
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < m ;j ++) {
            cin >> adj[i][j] ;
        }
    }

    vector<vector<int>>vis(n,vector<int>(m,0));
    ll ans = 0 ; // number of connected component
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < m ;j++) {
            if (!vis[i][j] && adj[i][j]=='.') {
                dfs(i,j,adj,vis);
                ans++;
            }
        }
    }
    cout << ans << endl ;
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

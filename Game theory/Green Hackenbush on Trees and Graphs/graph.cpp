const int N = 2e5 + 10;
vector<int> g[N];
int n, T, low[N], dis[N];

int dfs(int u, int pre = 0) {
    dis[u] = low[u] = ++T;
    int ans = 0;
    for (auto v: g[u]) {
        if (v == pre) {
            pre += 2 * n;
            continue;
        }
        if (dis[v] == 0) {
            int res = dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dis[u])
                ans ^= (1 + res) ^ 1; /// bridge
            else
                ans ^= res; /// non bridge
        } else low[u] = min(low[u], dis[v]);
    }
    if (pre > n) pre -= 2 * n;
    for (auto v: g[u]) if (v != pre && dis[u] <= dis[v]) ans ^= 1;
    return ans;
}

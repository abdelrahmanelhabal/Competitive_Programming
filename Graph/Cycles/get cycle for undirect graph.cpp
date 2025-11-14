int const N = 1e5+5;
int n , m , cycle_start, cycle_end , parent[N];
char visited[N];
vector<int>adj[N];

bool dfs(int v, int par) {
    visited[v] = true;
    for (int u : adj[v]) {
        if(u == par) continue;
        if (visited[u]) {
            cycle_end = v;
            cycle_start = u;
            return true;
        }
        parent[u] = v;
        if (dfs(u, parent[u]))
            return true;
    }
    return false;
}

vector<int> find_cycle() {
    for (int i = 0 ; i < n; i ++) {
        visited[i] = 0 ;
        parent[i] = -1;
    }
    cycle_start = -1;

    for (int v = 0; v < n; v++) {
        if (!visited[v] && dfs(v, parent[v]))
            break;
    }
    vector<int> cycle;
    if (cycle_start != -1) {
        cycle.push_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent[v])
            cycle.push_back(v);
        cycle.push_back(cycle_start);
    }
    return cycle;
}    

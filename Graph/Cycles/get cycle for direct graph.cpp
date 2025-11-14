int const N = 1e5+5;
int n , m , cycle_start , cycle_end , parent[N] ;
char color[N];
vector<int>adj[N];


bool dfs(int v) {
    color[v] = 1;
    for (int u : adj[v]) {
        if (color[u] == 0) {
            parent[u] = v;
            if (dfs(u))
                return true;
        } else if (color[u] == 1) {
            cycle_end = v;
            cycle_start = u;
            return true;
        }
    }
    color[v] = 2;
    return false;
}

vector<int> find_cycle() {
    for (int i = 0 ; i < n ; i++) {
        color[i] = 0 ;
        parent[i] = -1 ;
    }
    cycle_start = -1;

    for (int v = 0; v < n; v++) {
        if (color[v] == 0 && dfs(v))
            break;
    }

    vector<int> cycle;
    if (~cycle_start) {
        cycle.push_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent[v])
            cycle.push_back(v);
        cycle.push_back(cycle_start);
        reverse(cycle.begin(), cycle.end());
    }
    return cycle;
}
   

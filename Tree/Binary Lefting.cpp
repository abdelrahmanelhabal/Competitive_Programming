int const Log = 40 , N = 1e5+5;
int n ,  parent[N] ,up[N][Log];
void build() {
    for (int i = 0 ; i < n ; i++) {
        up[i][0] = parent[i] ;
    }
    for (int i = 1 ; i < Log ; i++) {
        for (int j = 0; j < n ; j++) {
            up[j][i] = up[up[j][i-1]][i-1];
        }
    }
}
int kth_ancestor(int node , int k) {
    for (int i = 0 ; i < Log ; i++) {
        if ( k >> i & 1) {
            node = up[node][i];
        }
    }
    return node;
}
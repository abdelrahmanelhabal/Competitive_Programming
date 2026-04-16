int const N = 2e5 + 10 ;
vector<int>adj[N];
int n , k , sz[N] , cnt[N], ans = 0;
bool removed[N] ;
int dfs_sz(int u , int par){
    sz[u] = 1 ;
    for(auto v : adj[u]){
        if(v == par || removed[v]) continue;
        sz[u] += dfs_sz(v,u);
    }
    return sz[u];
}
int dfs_centroid(int u , int par , int s){
    for(auto v : adj[u]){
        if(v == par || removed[v]) continue;
        if(sz[v] * 2 > s) return dfs_centroid(v, u , s);
    }
    return u ;
}
void dfs_add(int u , int par , int delta , int depth = 1){
    for(auto v : adj[u]){
        if(v == par || removed[v]) continue;
        dfs_add(v , u , delta , depth + 1);
    }
}
void dfs_ans(int u , int par , int depth = 1){
    for(auto v : adj[u]){
        if(v == par || removed[v])continue;
        dfs_ans(v , u , depth + 1);
    }
}
void decompose(int u){
    int comp_sz = dfs_sz(u , -1);
    int centroid = dfs_centroid(u , -1 , comp_sz) ;
 
    for(auto v : adj[centroid]){
        if(removed[v])continue;
        dfs_ans(v , centroid);
        dfs_add(v , centroid , 1);
    }
 
    for(auto v : adj[centroid]){
        if(removed[v])continue;
        dfs_add(v , centroid , -1);
    }
    
    removed[centroid] = true;
    for(auto v : adj[centroid]){
        if(removed[v])continue;
        decompose(v);
    }
}

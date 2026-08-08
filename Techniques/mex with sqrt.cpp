void add(int u) {
    if(val[u] == -1) return; // val[u] > n 
    int v = val[u];
    if(freq[v] == 0) blk[v / block_size]--;
    freq[v]++;
}
void erase(int u) {
    if(val[u] == -1)return;
    int v = val[u] ;
    if(freq[v] == 1) blk[v / block_size]++;
    freq[v]--;
}
int get_mex(){
    int blocks = (n + block_size) / block_size ; 

    for(int i = 0 ; i <= blocks ; i++){
        if(blk[i] == 0)continue;

        int l = i * block_size ; 
        int r = min(n , l + block_size - 1);
        for(int v = l ; v <= r ;v++){
            if(freq[v] == 0) return v ; 
        }
    }
    return n ; 
}

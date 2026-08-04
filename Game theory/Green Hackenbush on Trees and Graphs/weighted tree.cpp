int dfs(int u,int p){
    int sg = 0;

    for(auto [v,w] : adj[u]){
        if(v == p) continue;

        int child = dfs(v,u);

        if(w == 1)
            sg ^= child + 1;
        else if(w % 2 == 0)
            sg ^= child;
        else
            sg ^= child ^ 1;
    }

    return sg;
}

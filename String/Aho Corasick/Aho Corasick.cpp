struct AHO{
    int N ; 
    static const int A = 26 ; 
    static const int MAXN = 200005 ;
 
    int link[MAXN] , out_link[MAXN];
    int nxt[MAXN][A];
    vector<int>  out[MAXN] , adj[MAXN];
 
    AHO():N(0){
        node();
    }
 
    int node(){
        fill(nxt[N], nxt[N] + A, 0);
        link[N] = 0;
        out_link[N] = 0;
        out[N].clear();
        return N++;
    }
 
    int get(char c){
        return c - 'a';
    }
 
    int insert(string &s , int idx){
        int u = 0 ; 
        for(auto c : s){
            if(nxt[u][get(c)] == 0) nxt[u][get(c)] = node();
            u = nxt[u][get(c)];
        }
        out[u].emplace_back(idx);
        return u ; 
    }
 
    void build(){
        queue<int> q; 
        for(int c = 0 ; c < A ; c++){
            if(nxt[0][c]) q.emplace(nxt[0][c]);
        }
        while(q.size()){
            auto u = q.front(); q.pop();
            for(int c = 0 ; c < A ; c++){
                int v = nxt[u][c] ; 
                if(v == 0) nxt[u][c] = nxt[link[u]][c];
                else{
                    link[v] = nxt[link[u]][c];
                    out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
                    q.emplace(v);
                }
            }            
        }
    }
 
    int advance(int u , char c){
        return nxt[u][get(c)]; 
    } 
};

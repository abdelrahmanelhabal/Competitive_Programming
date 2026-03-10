// 0 -> from [l , r] to v
// 1 -> from v to [l , r]
const int N = 1e5 + 5;
int tree[2][4*N] , n , idx ;
vector<pair<int,int>>adj[4 * N];
void init(){ idx = n; }
void add(int u , int v , int w = 0){
    adj[u].emplace_back(v , w);
}
void build(int node , int l , int r ){
    if(l == r){
        tree[0][node] = tree[1][node] = l ;
        return;
    }
    int mid = (l + r) >> 1;
    for (int i = 0; i < 2 ; ++i) {
        tree[i][node] = idx++;
    }
    build(node * 2 , l  , mid);
    build(node * 2  + 1, mid + 1 , r);
    add(tree[0][node * 2] , tree[0][node] );
    add(tree[0][node * 2 + 1] , tree[0][node]);
    add(tree[1][node] , tree[1][node * 2]);
    add(tree[1][node] , tree[1][node * 2 + 1]);
}
void connect(int node , int l , int r , int xl , int xr , int v , int cost , bool flag){
    if(xr < l || xl > r)return;
    if(xl >= l && xr <= r){
        if(flag == 0){
            add(tree[0][node] , v , cost);
        }else{
            add(v , tree[1][node] , cost);
        }
        return;
    }
    int mid = (xl + xr) >> 1;
    connect(node * 2 , l , r , xl , mid , v , cost , flag);
    connect(node * 2 + 1, l , r , mid + 1 , xr , v , cost , flag);
}
void connect(int l , int r , int v , int cost , int f){
    connect(1 , l , r , 0 , n - 1 , v , cost , f);
}

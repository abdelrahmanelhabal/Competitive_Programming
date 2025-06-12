int const N = 2e5+5  , Sq = 600 ;
int a[N] , BlkAnswer[Sq];
vector<vector<int>>Blk(Sq);
int n , q ;
void init() {
    for (int i = 0 ; i < n ; i++) {
        Blk[i/Sq].emplace_back(a[i]);
        BlkAnswer[i/Sq] += a[i];
    }
}
void update(int idx , int val) {
    int Blk_idx = idx/Sq , idx_in_blK = idx%Sq;
    BlkAnswer[Blk_idx] -= a[idx] ;
    BlkAnswer[Blk_idx] += val ;
    a[idx] = val ;
    Blk[Blk_idx][idx_in_blK] = val ;

}
int get(int l , int r) {
    int res = 0 ;
    while (l <= r) {
        if (l%Sq == 0 && l + Sq <= r) {
            res+=BlkAnswer[l/Sq];
            l+=Sq;
        }
        else {
            res+=a[l];
            l++;
        }
    }
    return res;
}
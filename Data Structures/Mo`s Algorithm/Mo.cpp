int block_size = 370 ;
struct Query {
    int l  ,r  , idx  ;
    Query(int l , int r , int idx) : l(l), r(r), idx(idx) {}
    bool operator<(const Query& other) const {
        int n1 = l / block_size, n2 = other.l / block_size;
        if (n1 != n2) return n1 < n2;
        return (n1 & 1) ? r > other.r : r < other.r ;
    }
};
void add(int MoIdx ) {

}
void erase(int MoIdx) {
}
void Mo(vector<Query> &queries) {
    int MoLeft = 0,MoRight = -1;
    for(auto &q: queries) {
        while(MoRight < q.r) add(++MoRight);
        while(MoLeft > q.l) add(--MoLeft);
        while(MoRight > q.r) erase(MoRight--);
        while(MoLeft < q.l) erase(MoLeft++);
        // ans[q.idx] = res ;
    }
}

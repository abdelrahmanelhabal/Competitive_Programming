int SQ = 2154;
const int N = 1e5 + 5;
int val[N] , ans[N] , cur[N] , res = 0  ,L = 0 , R = -1 , T = 0  ;
vector<int>all;
struct Query {
    int l, r, t, idx;
    bool operator<(const Query &other) const {
        int b1_l = l / SQ;
        int b2_l = other.l / SQ;
        if (b1_l != b2_l) return b1_l < b2_l;
 
        int b1_r = r / SQ;
        int b2_r = other.r / SQ;
        if (b1_r != b2_r) {
            if (b1_l & 1) return b1_r < b2_r;
            return b1_r > b2_r;
        }
 
        // Sort by Time
        if (b1_r & 1) return t < other.t;
        return t > other.t;
    }
};
struct Update {
    int pos;
    int old_val;
    int new_val;
};
vector<Update> update ;
vector<Query> query ;
void add(int idx){
}
void remove(int idx){

}
void apply_update(int idx , int dir){
    int pos = update[idx].pos ; 
    bool in_window = (L <= pos && pos <= R) ;
    if(in_window){
        remove(pos);
    } 
    if(dir == 1){
        val[pos] = update[idx].new_val ; 
    }
    else{
        val[pos] = update[idx].old_val ; 
    }
    if(in_window){
        add(pos);
    }
}
void MO(){
    for (auto &[l, r, t, idx] : query) {
        while (T < t) apply_update(T++, 1);
        while (T > t) apply_update(--T, -1);
        while (R < r) add(++R);
        while (L > l) add(--L);
        while (R > r) remove(R--);
        while (L < l) remove(L++);
        // ans[idx] = res; 
    }
}

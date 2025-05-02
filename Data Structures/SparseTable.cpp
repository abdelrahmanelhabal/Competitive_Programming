const int N = 1e6 , LOG = 20;
struct Node {
    int val ;
    Node operator+(const Node&other) const {
        Node res{};
        res.val = gcd(val, other.val);
        return res;
    }
} spt[N][LOG] ;

struct sparse_Table{
    void init(vector<int>&a) { // build  sparse table 
        int n = a.size();
        for (int i = 0 ; i < n; i++) { spt[i][0]=Node{a[i]}; }

        for (int k = 1; (1ll<<k) <= n ; k++ ) {
            for (int i = 0 ; i +(1ll<<k) <= n ; i++) {
                spt[i][k]=spt[i][k-1]+spt[i+(1ll<<(k-1))][k-1];
            }
        }
    }

    int qry(int l , int r) { //o(1)
        int k = 31 - __builtin_clz(r-l+1);
        return (spt[l][k]+spt[r-(1ll<<k)+1][k]).val;
    }
    int Query2(int l, int r) { // O(log N)
        Node ans = Node{0};
        for (int j = LOG - 1; j >= 0; --j) {
            if ((1 << j) <= r - l + 1) {
                ans = ans + spt[l][j];
                l += (1 << j);
            }
        }
        return ans.val;
    }
};
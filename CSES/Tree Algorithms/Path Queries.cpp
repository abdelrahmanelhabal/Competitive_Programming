#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'

vector<vector<int>>adj;
vector<int>in,out , val ;
int timer ;
void dfs(int node , int parent) {
    in[node] = ++timer;
    for (auto child : adj[node]) {
        if (child == parent)continue;
        dfs(child,node);
    }
    out[node] = timer;
}
struct Node {
    int val , lazy  = 0 ;
    bool isLazy = false  ;
    Node() { val = 0;  }
    Node(int x ) { val = x;  }
    void update(int x , int lx , int rx) {
        val += (x * (rx-lx)) ;
        lazy += x;
        isLazy = true ;
    }
};
struct lazySegTree {
    int tree_size;
    vector<Node> segData ;

    lazySegTree(int n) {
        tree_size = 1;
        while (tree_size < n) tree_size *= 2 ;
        segData.resize(2 * tree_size, Node(0));
    }

    Node merge(Node &left, Node &right) {
        Node ans;
        ans.val = left.val + right.val;
        return ans;
    }

    void propagate(int node, int lx, int rx) {
        if (rx - lx == 1 || !segData[node].isLazy) return;
        int mid = (lx + rx) / 2;
        segData[2 * node + 1].update(segData[node].lazy, lx, mid);
        segData[2 * node + 2].update(segData[node].lazy, mid, rx);
        segData[node].isLazy = false;
        segData[node].lazy = 0 ;
    }
    void update(int l, int r , int val , int node, int lx, int rx) {
        propagate(node, lx, rx);
        if (lx >= r || rx <= l) return ;
        if (lx >= l && rx <= r) {
            segData[node].update(val,lx,rx);
            return;
        }
        int mid = (lx + rx) / 2;
        update(l, r,val, 2 * node + 1, lx, mid);
        update(l, r,val, 2 * node + 2, mid, rx);
        segData[node] = merge(segData[2 * node + 1], segData[2 * node + 2]);
    }

    void update(int l, int r, int val) {
        return update(l, r , val , 0, 0, tree_size);
    }
    Node get(int l, int r, int node, int lx, int rx) {
        propagate(node, lx, rx);
        if (lx >= r || rx <= l) return Node(0);
        if (lx >= l && rx <= r) return segData[node];
        int mid = (lx + rx) / 2;
        Node left = get(l, r, 2 * node + 1, lx, mid);
        Node right = get(l, r, 2 * node + 2, mid, rx);
        return merge(left, right);
    }

    Node get(int l, int r) {
        return get(l, r, 0, 0, tree_size);
    }
};

void solve() {
int n , q ; cin >> n >> q ;
    adj.resize(n+1);
    in.resize(n+1);
    out.resize(n+1);
    val.resize(n+1);
    for (int i = 1 ; i <= n ; i++) {
        cin >> val[i];
    }
    for (int i = 1; i < n ; i++) {
        int u , v ; cin >> u >> v ;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    timer = 0 ;
    dfs(1,1);
    lazySegTree s(2*n);
    for (int i = 1 ; i <=n ; i++) {
        s.update(in[i], out[i]+1, val[i]);
    }
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int node , c ; cin >> node >> c ;
            s.update(in[node], out[node]+1, c-val[node]);
            val[node]=c;
        }
        else {
            int node ; cin >> node;
            cout << s.get(in[node],in[node]+1).val << endl ;
        }
    }
}


signed main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int tc =1;  //cin >> tc ;
    while (tc--) solve();
    return 0;
}

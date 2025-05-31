#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define str string
#define int long long
#define ld long double
#define endl '\n'
vector<vector<int>>adj;
vector<int>in,out , color;
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
    int val ;
    Node() { val = 0 ;}
    Node(int val) { this->val = val ;}
    void change(int x) { val = x ; }
};

struct segTree {
    int tree_size;
    vector<Node> segData;

    segTree(int n) {
        tree_size = 1;
        while (tree_size < n) tree_size *= 2;
        segData.resize(2 * tree_size, Node());
    }

    Node merge(Node &left, Node &right) {
        Node ans;
        ans.val = left.val + right.val;
        return ans;
    }

    void init(vector<int> &a, int node, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int)a.size()) {
                segData[node] = Node(a[lx]);
            }
            return;
        }
        int mid = (lx + rx) / 2;
        init(a, 2 * node + 1, lx, mid);
        init(a, 2 * node + 2, mid, rx);
        segData[node] = merge(segData[2 * node + 1], segData[2 * node + 2]);
    }

    void init(vector<int> a) {
        init(a, 0, 0, tree_size);
    }

    void set(int idx, int val, int node, int lx, int rx) {
        if (rx - lx == 1) {
            segData[node].change(val);
            return;
        }
        int mid = (lx + rx) / 2;
        if (idx < mid) set(idx, val, 2 * node + 1, lx, mid);
        else set(idx, val, 2 * node + 2, mid, rx);
        segData[node] = merge(segData[2 * node + 1], segData[2 * node + 2]);
    }

    void set(int idx, int val) {
        set(idx, val, 0, 0, tree_size);
    }

    Node get(int l, int r, int node, int lx, int rx) {
        if (lx >= r || rx <= l) return Node();
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
    int n , q  ; cin >>n  >> q ;
    adj.resize(n+1);
    color.resize(n+1);
    out.resize(n+1);
    in.resize(n+1);
    for (int i = 1 ; i <= n ; i++) {cin >> color[i];}
    for (int i = 0 ; i < n-1 ; i++) {
        int u , v ; cin >> u >> v ;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    timer = 0 ;
    dfs(1,1);

    segTree s(n+5);
    for (int i = 1 ; i <=n ; i++) {
        s.set(in[i],color[i]);
    }

    while (q--) {
        int type ; cin >> type;
        if (type == 1) {
            int node , val ; cin >> node >> val ;
            s.set(in[node],val);
        }
        else {
            int node ; cin >> node ;
            cout << s.get(in[node],out[node]+1).val << endl ;
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

struct RollBack {
    vector<int> parent , group ;
    stack<tuple<int,int,int>> back;
    int comp  , mx;
    void init(int n) {
        comp = n ;
        mx = 1 ;
        parent.resize(n+1);
        group.resize(n+1);
        for (int i = 0 ; i<=n;i++) { parent[i] = i; group[i] = 1;}
    }

    int find(int node) {
        if (parent[node] == node) return node;
        return find(parent[node]);
    }

    bool merge(int u , int v) {
        int leaderU = find(u);
        int leaderV = find(v);
        if (leaderU == leaderV) {
            back.emplace(-1,-1,-1);
            return false;
        }
        if (group[leaderU] > group[leaderV]) {swap(leaderU, leaderV);}
        back.emplace(leaderU,leaderV,mx);
        parent[leaderU] = leaderV;
        group[leaderV] += group[leaderU];
        mx = max(mx,group[leaderV]);
        comp--;
        return true;
    }
    void rollBack(int step) {
        while (step--) {
            if (back.empty()) return;
            auto [leaderU,leaderV,prev_mx] = back.top(); back.pop();
            if (leaderU == -1)continue;
            parent[leaderU] = leaderU;
            group[leaderV] -= group[leaderU];
            mx = prev_mx ;
            comp++;
        }
    }
    int get_size(int node) { return group[find(node)]; }
    int get_max_size() {return mx;}
    bool sameGroup(int u , int v){return find(u)==find(v);}
};
struct Query {
    int l  , r , idx ;
    Query(int l ,int r , int idx): l(l), r(r), idx(idx) {}
    bool operator<(const Query& other ) const {
        return r < other.r;
    }
};
int const N = 5e5 + 10  ;
int n , m , q , ans[N] , block_size = 0  ;
pair<int,int> edges[N];
vector<Query>Buckets[600];
void solve() {
    cin >> n >> m  ;
    for (int i = 0 ; i< m ; i++) {
        cin >> edges[i].first >> edges[i].second;
        edges[i].first--;
        edges[i].second--;
    }
    cin >> q ;
    block_size = (int)(sqrt(m) + 1);
    int tot = (m + block_size -1)/block_size;

    for (int i = 0 ; i <  tot; i++) {Buckets[i].clear();}

    for (int i = 0 ; i <  q; i++) {
        int l , r ; cin >> l >> r ;
        l--,r--;
        Buckets[l / block_size].emplace_back(l,r,i);
    }
    for (int i = 0 ; i < tot ; i++) {
        if (Buckets[i].empty()) continue;
        sort(all(Buckets[i]));
        RollBack d ;
        d.init(n);
        int base = (i + 1) * block_size;
        int r = base ;
        for (auto &qu : Buckets[i]) {
            while (r <= qu.r) {
                int u = edges[r].first , v = edges[r].second;
                d.merge(u,v);
                r++;
            }
            int count = 0 ;
            while (qu.l < min(base , qu.r+1)) {
                int u = edges[qu.l].first , v = edges[qu.l].second;
                d.merge(u,v);
                qu.l++;
                count++;
            }
            ans[qu.idx] = d.comp;
            d.rollBack(count);
        }
    }
    for (int i = 0 ; i < q ; i++) {
        cout << ans[i] << endl  ;
    }
}

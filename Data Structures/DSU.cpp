struct DSU {
    vector<ll> parent , group ;
    ll comp  , mx;
    void init(ll n) {
        comp = n ;
        mx = 1 ;
        parent.resize(n+1);
        group.resize(n+1);
        for (ll i = 0 ; i<=n;i++) { parent[i] = i; group[i] = 1;}
    }

    ll find(ll node) {
        if (parent[node] == node) return node;
        return parent[node] = find(parent[node]);
    }

    bool merge(ll u , ll v) {
        ll leaderU = find(u);
        ll leaderV = find(v);
        if (leaderU == leaderV) {return false;}
        if (group[leaderU] > group[leaderV]) {swap(leaderU, leaderV);}
        parent[leaderU] = leaderV;
        group[leaderV] += group[leaderU];
        mx = max(mx,group[leaderV]);
        comp--;
        return true;
    }
    ll get_size(ll node) { return group[find(node)]; }
    ll get_max_size() {return mx;}
    bool sameGroup(ll u , ll v){return find(u)==find(v);}
};
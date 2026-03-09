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
struct Query{
    int type , u , v ;
};

vector<Query> queries;

struct segment_tree{
    int sz;
    vector<vector<pair<int,int>>> segData;

    segment_tree(int n){
        sz = 1;
        while(sz < n) sz*=2;
        segData.assign(2*sz,{});
    }

    void add_edge(int l , int r , pair<int,int> edge , int node , int lx , int rx){
        if(rx<=l || lx>=r) return;

        if(l<=lx && rx<=r){
            segData[node].push_back(edge);
            return;
        }

        int mid = (lx + rx) / 2 ;

        add_edge(l , r , edge ,2*node+1 , lx ,mid);
        add_edge(l , r , edge , 2*node+2 , mid , rx);
    }

    void add_edge(int l,int r,pair<int,int> edge){
        add_edge(l,r,edge,0,0,sz);
    }
};

void dfs(int node,int lx,int rx, segment_tree &st , RollBack &dsu){

    int used=0;

    for(auto [u , v]:st.segData[node]){
        dsu.merge(u,v);
        used++;
    }

    if (rx - lx == 1) {
        if(lx > 0 && lx < queries.size()){
            cout << dsu.comp << endl ;
        }
    }
    else{
        int mid = (lx + rx) / 2 ;

        dfs(2*node+1,lx,mid,st,dsu);
        dfs(2*node+2,mid,rx,st,dsu);
    }
    dsu.rollBack(used);
}


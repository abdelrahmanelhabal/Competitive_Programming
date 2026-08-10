int const N = 1e5 + 5 , INF = 1e18; 
int n, k , dp[2][N] ;
void dnc(int idx , int l , int r , int optl , int optr) {
    if(l > r)
        return;
    int mid = (l + r) / 2 , opt = optl ,prev = (idx - 1) & 1 , cur = idx & 1;
    for(int i = optl; i <= min(mid , optr); ++i) {
        int ret = dp[prev][i - 1] + cost(i , mid);
        if(ret < dp[cur][mid]) {
            dp[cur][mid] = ret;
            opt = i;
        }
    }
    dnc(idx , l , mid - 1 , optl , opt);
    dnc(idx , mid + 1 , r , opt , optr);
}

void solve() {
    cin >> n >> k ; 
    for (int j = 0; j <= n; ++j) {
        dp[0][j] = INF;
    }

    dp[0][0] = 0;

    for (int i = 1;i <= k;i++) {
        for(int j = 0; j <= n; ++j) {
            dp[i & 1][j] = INF;
        }
        dnc(i , 1 , n , 1 , n);
    }
    cout << dp[k & 1][n] << endl ;
}

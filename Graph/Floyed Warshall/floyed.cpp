int const INF = 1e18 ;
    for (int i = 0 ; i< n ; i++) {
        for (int j = 0 ; j < n ; j++) {
            dp[i][j]= INF;
        }
    }
    
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < n;j++) {
            dp[i][j] = adj[i][j];
        }
    }
    for(int k = 0;k < n;k++){
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                dp[i][j] = min(dp[i][j] , dp[i][k] + dp[k][j]);
            }
        }
    }

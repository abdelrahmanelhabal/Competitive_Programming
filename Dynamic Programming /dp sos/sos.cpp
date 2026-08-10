// adding subset to superset 
void forward1(vector<int>& dp, const int numBits) {
    for (int bit = 0; bit < numBits; bit++) {
        for (int mask = 1; mask < (int)dp.size(); mask++) {
            if (mask & (1 << bit))
                dp[mask] += dp[mask ^ (1 << bit)];
        }
    }
}
// adding superset to subset 
void forward2(vector<int>& dp, const int numBits) {
    for (int bit = 0; bit < numBits; bit++) {
        for (int mask = 1; mask < (int)dp.size(); mask++) {
            if (mask & (1 << bit))
                dp[mask ^ (1 << bit)] += dp[mask];
        }
    }
}
// undo subset to super set 
void backward1(vector<int>& dp, const int numBits) {
    for (int bit = 0; bit < numBits; bit++) {
        for (int mask = (int)dp.size() - 1; mask > 0; mask--) {
            if (mask & (1 << bit))
                dp[mask] -= dp[mask ^ (1 << bit)];
        }
    }
}
// undo superset to subset 
void backward2(vector<int>& dp, const int numBits) {
    for (int bit = 0; bit < numBits; bit++) {
        for (int mask = (int)dp.size() - 1; mask > 0; mask--) {
            if (mask & (1 << bit))
                dp[mask ^ (1 << bit)] -= dp[mask] ;
        }
    }
}





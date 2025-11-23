vector<int> prev_smaller(vector<int>&a) {
    int n = a.size();
    vector<int>res(n,-1);
    stack<int>s;
    for (int i = 0 ; i < n ; i++) {
        while (!s.empty() && a[s.top()] > a[i] ) s.pop();
        if (!s.empty()) {
            res[i] = s.top() ; // 0-base
        }
        s.push(i);
    }
    return res;
}

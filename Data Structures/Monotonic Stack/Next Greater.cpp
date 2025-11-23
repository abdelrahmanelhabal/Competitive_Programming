vector<int>next_greater(vector<int>&a) {
    int n = a.size();
    vector<int>res(n,n);
    stack<int>s;
    for (int i = n-1 ; i >=0 ; i--) {
        while (!s.empty() && a[s.top()] <= a[i]) s.pop();
        if (!s.empty()) {
            res[i] = s.top(); // 0-base
        }
        s.push(i);
    }
    return res;
}

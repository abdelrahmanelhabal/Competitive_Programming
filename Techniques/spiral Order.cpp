vector<int> spiralOrder(const vector<vector<int>> &a) {
    int n = a.size();
    int top = 0, left = 0, bottom = n - 1, right = n - 1;
    vector<int> res;
    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; ++j) res.push_back(a[top][j]);
        ++top;
        for (int i = top; i <= bottom; ++i) res.push_back(a[i][right]);
        --right;
        if (top <= bottom) {
            for (int j = right; j >= left; --j) res.push_back(a[bottom][j]);
            --bottom;
        }
        if (left <= right) {
            for (int i = bottom; i >= top; --i) res.push_back(a[i][left]);
            ++left;
        }
    }
    return res;
}

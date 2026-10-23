/*
 * ============================================================
 * PROBLEM: Lizard Era: Beginning
 * ============================================================
 * The hero has three companions: Lynn (L), Meliana (M) and
 * Worrigan (W). There are n mandatory quests (1 <= n <= 25).
 * For each quest the hero must take exactly two companions.
 * Quest i changes the attitude of the chosen companions:
 *   Lynn by l[i], Meliana by m[i], Worrigan by w[i]
 * (|values| <= 10^7). All attitudes start at 0.
 *
 * Goal: choose the pair for every quest so that, after all
 * quests, the three attitudes are EQUAL. If there are several
 * ways, pick the one with the greatest final attitude.
 * Print the pair for each quest (e.g. "LM"), or "Impossible".
 *
 * Example:
 *   3
 *   1 0 0
 *   0 1 0
 *   0 0 1
 *   -> LM / MW / MW   (all three end at 1)
 *
 * ============================================================
 * SOLUTION: Meet in the middle
 * ============================================================
 * Brute force: 3 choices per quest -> 3^25 (about 8.5 * 10^11),
 * far too slow.
 *
 * Idea:
 *   1. Split the quests into two halves: the first h1 = n / 2
 *      and the remaining h2 = n - h1. Each half has at most
 *      3^13 (about 1.6 million) possible choices.
 *   2. The final attitudes (A, B, C) are equal exactly when
 *        A - B = 0   and   B - C = 0.
 *      So for each choice in a half, only the pair
 *        key = (a - b, b - c)
 *      matters, plus the value a (the attitude to maximize).
 *   3. First half: enumerate all choices, store in a map
 *        key -> (best a, mask of choices)
 *      keeping the largest a for each key.
 *   4. Second half: enumerate all choices. A matching first-half
 *      state must have key = (-(a - b), -(b - c)), so that the
 *      differences cancel. Look it up in the map. The final
 *      attitude is (a of first half) + (a of second half); keep
 *      the maximum.
 *   5. Choices are stored as base-3 masks (0 = "LM", 1 = "LW",
 *      2 = "MW"), then decoded to print the answer.
 *      If nothing matched, print "Impossible".
 *
 * Complexity:
 *   Time : O(3^(n/2) * log)   (map lookups)
 *   Space: O(3^(n/2))
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define endl '\n'

int n, l[25], m[25], w[25];
map<pair<int, int>, pair<int, int>> mp;  // key -> (best a, mask)
int h1, h2;
int bestVal = -1e18, bestM1 = -1, bestM2 = -1;

// First half: store every reachable state in the map
void dfs1(int i, ll a, ll b, ll c, int mask, int mul) {
    if (i == h1) {
        auto it = mp.find(make_pair(a - b, b - c));
        if (it == mp.end() || it->second.first < a)
            mp[make_pair(a - b, b - c)] = {a, mask};
        return;
    }
    dfs1(i + 1, a + l[i], b + m[i], c,        mask + 0 * mul, mul * 3);  // LM
    dfs1(i + 1, a + l[i], b,        c + w[i], mask + 1 * mul, mul * 3);  // LW
    dfs1(i + 1, a,        b + m[i], c + w[i], mask + 2 * mul, mul * 3);  // MW
}

// Second half: look for a first-half state that cancels the differences
void dfs2(int i, ll a, ll b, ll c, int mask, int mul) {
    if (i == n) {
        auto it = mp.find(make_pair(-(a - b), -(b - c)));
        if (it != mp.end() && it->second.first + a > bestVal) {
            bestVal = it->second.first + a;
            bestM1 = it->second.second;
            bestM2 = mask;
        }
        return;
    }
    dfs2(i + 1, a + l[i], b + m[i], c,        mask + 0 * mul, mul * 3);  // LM
    dfs2(i + 1, a + l[i], b,        c + w[i], mask + 1 * mul, mul * 3);  // LW
    dfs2(i + 1, a,        b + m[i], c + w[i], mask + 2 * mul, mul * 3);  // MW
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> l[i] >> m[i] >> w[i];

    h1 = n / 2;
    h2 = n - h1;

    dfs1(0, 0, 0, 0, 0, 1);
    dfs2(h1, 0, 0, 0, 0, 1);

    if (bestM1 < 0) {
        cout << "Impossible" << endl;
        return;
    }

    // Decode base-3 masks back to pairs
    vector<string> s = {"LM", "LW", "MW"};
    for (int i = 0; i < h1; i++) {
        cout << s[bestM1 % 3] << endl;
        bestM1 /= 3;
    }
    for (int i = 0; i < h2; i++) {
        cout << s[bestM2 % 3] << endl;
        bestM2 /= 3;
    }
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}

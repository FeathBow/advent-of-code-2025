#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define int long long
#define all(x) (x).begin(), (x).end()
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    vector<string> g;
    string s;
    while (cin >> s) g.push_back(s);
    int n = g.size(), m = g[0].size();
    int Si = -1, Sj = -1, ans = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (g[i][j] == 'S') Si = i, Sj = j;
    vector<vector<int>> dp(n, vector<int>(m));
    queue<array<int, 2>> que;
    dp[Si][Sj] = 1;
    que.push({Si, Sj});
    while (que.size()) {
        auto [x, y] = que.front();
        que.pop();
        if (not dp[x][y]) continue;
        int val = dp[x][y];
        dp[x][y] = 0;
        if (g[x][y] == '^') {
            if (y - 1 < 0) ans += val;
            else
                dp[x][y - 1] += val, que.push({x, y - 1});
            if (y + 1 >= m) ans += val;
            else
                dp[x][y + 1] += val, que.push({x, y + 1});
        } else {
            if (x + 1 >= n) ans += val;
            else
                dp[x + 1][y] += val, que.push({x + 1, y});
        }
    }
    cout << ans << '\n';
    return 0;
}
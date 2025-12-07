#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define int long long
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    vector<string> g;
    string s;
    while (cin >> s) g.push_back(s);
    int n = g.size(), m = g[0].size();
    int Si = -1, Sj = -1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (g[i][j] == 'S') Si = i, Sj = j;

    queue<array<int, 2>> que;
    vector<vector<int>> vis(n, vector<int>(m));
    que.push({Si, Sj});
    int ans = 0;
    while (que.size()) {
        auto [x, y] = que.front();
        que.pop();
        if (x < 0 or x >= n or y < 0 or y >= m or vis[x][y]) continue;
        vis[x][y] = 1;
        if (g[x][y] == '^') ++ans, que.push({x, y - 1}), que.push({x, y + 1});
        else
            que.push({x + 1, y});
    }
    cout << ans << '\n';
    return 0;
}

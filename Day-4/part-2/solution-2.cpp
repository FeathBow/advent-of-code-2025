#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define int long long
vector<array<int, 2>> dir = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int n = 140;
    vector<vector<char>> g(n + 2, vector<char>(n + 2));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) cin >> g[i][j];
    vector<vector<int>> in(n + 2, vector<int>(n + 2)), vis(n + 2, vector<int>(n + 2));
    queue<array<int, 2>> que;
    auto check = [&](int x, int y) { return x >= 1 and x <= n and y >= 1 and y <= n; };
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            if (g[i][j] != '@') continue;
            for (auto [dx, dy] : dir)
                if (check(i + dx, j + dy) and g[i + dx][j + dy] == '@') ++in[i][j];
            if (in[i][j] < 4) que.push({i, j});
        }

    int ans = 0;
    while (not que.empty()) {
        auto [x, y] = que.front();
        que.pop();
        if (vis[x][y] or g[x][y] != '@' or in[x][y] >= 4) continue;
        vis[x][y] = 1, g[x][y] = '.', ++ans;
        for (auto [dx, dy] : dir) {
            int nx = x + dx, ny = y + dy;
            if (not check(nx, ny) or vis[nx][ny] or g[nx][ny] != '@') continue;
            if (in[nx][ny]) --in[nx][ny];
            if (in[nx][ny] < 4) que.push({nx, ny});
        }
    }

    cout << ans << '\n';
    return 0;
}

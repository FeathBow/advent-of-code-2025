#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
#define int long long
vector<array<int, 2>> dir = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int n = 140;
    vector<vector<char>> g(n + 1, vector<char>(n + 1));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) cin >> g[i][j];
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            if (g[i][j] != '@') continue;
            int cnt = 0;
            for (auto [dx, dy] : dir)
                if (i + dx <= n and i + dx and j + dy <= n and j + dy) cnt += g[i + dx][j + dy] == '@';
            ans += cnt < 4;
        }
    cout << ans << '\n';
    return 0;
}

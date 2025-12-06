#include <iostream>
#include <vector>
using namespace std;
#define int long long
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int n = 1000, m = 5, ans = 0;
    vector<vector<int>> f(n, vector<int>(m));
    for (int _ = 0; _ < m - 1; ++_)
        for (int i = 0; i < n; ++i) cin >> f[i][_];
    char c;
    for (int i = 0; i < n; ++i) {
        cin >> c;
        if (c == '*') ans += f[i][0] * f[i][1] * f[i][2] * f[i][3];
        else
            ans += f[i][0] + f[i][1] + f[i][2] + f[i][3];
    }
    cout << ans << '\n';
    return 0;
}

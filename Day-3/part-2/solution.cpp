#include <algorithm>
#include <iostream>
#include <vector>
#define int long long
using namespace std;
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int t = 200;
    int ans = 0;
    while (t--) {
        string s;
        cin >> s;
        signed n = s.length();
        vector<vector<int>> dp(n, vector<int>(13, -(1 << 30)));
        dp[0][1] = s[0] - '0';
        for (int i = 0; i < n; ++i) dp[i][0] = 0;
        for (int i = 1; i < n; ++i)
            for (int j = 1; j <= min(12, n); ++j) dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] * 10 + s[i] - '0');
        ans += dp.back().back();
        cout << dp.back().back() << '\n';
    }
    cout << ans << '\n';
}
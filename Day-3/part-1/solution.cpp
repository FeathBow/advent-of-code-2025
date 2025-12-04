#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define int long long
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int ans = 0;
    for (int i = 1; i <= 200; ++i) {
        string s;
        cin >> s;
        vector<int> bac(s.length() + 1, -(1 << 30));
        for (int i = s.length() - 1; i; --i) bac[i] = max(bac[i + 1], (int) (s[i] - '0'));
        int res = 0;
        for (int i = 0; i < s.length(); ++i) res = max(res, (s[i] - '0') * 10 + bac[i + 1]);
    }
    cout << ans << '\n';
}

#include <iostream>
#include <vector>
using namespace std;
#define int long long
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int m = 5;
    vector<string> f(m);
    for (int _ = 0; _ < m; ++_) getline(cin, f[_]);
    int n = f[0].length(), ans = 0, res = 0;
    vector<int> cot;
    for (int i = n - 1; i >= 0; --i) {
        res = 0;
        for (int j = 0; j < m - 1; ++j)
            if (f[j][i] >= '0' and f[j][i] <= '9') res = res * 10 + (f[j][i] - '0');
        if (res) cot.emplace_back(res);

        if (f[m - 1][i] == '*' or f[m - 1][i] == '+') {
            if (f[m - 1][i] == '+')
                for (auto v : cot) ans += v;
            else {
                res = 1;
                for (auto v : cot) res *= v;
                ans += res;
            }
            vector<int>().swap(cot);
        }
    }
    cout << ans << '\n';
    return 0;
}

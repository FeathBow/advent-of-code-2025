#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
#define int long long
#define all(x) (x).begin(), (x).end()
constexpr int inf = 1 << 30;
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    string s;
    map<int, int> cot;
    while (cin >> s) {
        int dash = s.find('-');
        if (dash == string::npos) break;
        int l = stoll(s.substr(0, dash)), r = stoll(s.substr(dash + 1));
        ++cot[l], --cot[r + 1];
    }
    int res = 0, pos = 0, val = 0, ans = 0;
    for (auto [l, r] : cot) {
        res += r;
        if (pos > 0) ans += l - val;
        pos = res, val = l;
    }
    cout << ans << '\n';
    return 0;
}

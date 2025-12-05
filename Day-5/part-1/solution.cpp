#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
#define int long long
#define all(x) (x).begin(), (x).end()
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    string s;
    map<int, int> cot;
    vector<int> val;
    while (cin >> s) {
        int dash = s.find('-');
        if (dash != string::npos) {
            int l = stoll(s.substr(0, dash)), r = stoll(s.substr(dash + 1));
            ++cot[l], --cot[r + 1];
        } else
            val.emplace_back(stoll(s));
    }
    sort(all(val));
    cot[val.back() + 1] = 0;
    int res = 0, pos = 0, ans = 0;
    auto it = cot.begin();
    while (pos < val.size()) {
        auto [l, r] = *it;
        if (val[pos] < l) ans += res > 0, ++pos;
        else {
            res += r;
            if (it != cot.end()) ++it;
        }
    }
    cout << ans << '\n';
    return 0;
}

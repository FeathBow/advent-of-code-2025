#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>
using namespace std;
#define int long long
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    set<int> cot;
    string s;
    cin >> s;

    vector<array<int, 2>> area;
    int pos = 0;
    while (pos < s.size()) {
        int dash = s.find('-', pos), comma = s.find(',', dash + 1);
        int l = stoll(s.substr(pos, dash - pos)),
            r = stoll(s.substr(dash + 1, (comma == string::npos ? s.size() : comma) - dash - 1));
        area.push_back({l, r});
        if (comma == string::npos) break;
        pos = comma + 1;
    }
    auto check = [&](int l, int n, string& t) {
        if (l == n or n / l < 2) return false;
        for (int pos = l; pos < n; pos += l)
            if (t.compare(0, l, t, pos, l) != 0) return false;
        return true;
    };
    for (auto [l, r] : area)
        for (int i = l; i <= r; ++i) {
            string t = to_string(i);
            int n = t.size(), judge = false;
            for (int l = 1; l * l <= n; ++l) {
                if (n % l) continue;
                int r = n / l;
                if (check(l, n, t) or l != r and check(r, n, t)) {
                    judge = true;
                    break;
                }
            }
            if (judge) cot.insert(i);
        }
    cout << accumulate(cot.begin(), cot.end(), 0ll) << '\n';
    return 0;
}

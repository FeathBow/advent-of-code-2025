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

    for (auto [l, r] : area)
        for (int i = l; i <= r; ++i) {
            string t = to_string(i);
            if (t.size() & 1) continue;
            int n = t.size();
            if (t.substr(0, n / 2) == t.substr(n / 2, n / 2)) cot.insert(i);
        }
    cout << accumulate(cot.begin(), cot.end(), 0ll) << '\n';
    return 0;
}
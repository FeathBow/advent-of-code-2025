#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>
using namespace std;
#define int long long
#define all(x) (x).begin(), (x).end()

signed main() {
    cin.tie(0)->sync_with_stdio(false);
    vector<array<int, 3>> poi, edges;
    int x, y, z;
    char c;
    while (cin >> x >> c >> y >> c >> z) poi.push_back({x, y, z});
    int n = poi.size(), cnt = 1000;
    vector<int> fa(n), siz(n, 1);
    iota(all(fa), 0);
    auto find = [&](auto&& find, int d) -> int { return fa[d] == d ? d : fa[d] = find(find, fa[d]); };
    auto calc = [&](int i, int j) -> int {
        return (poi[i][0] - poi[j][0]) * (poi[i][0] - poi[j][0]) + (poi[i][1] - poi[j][1]) * (poi[i][1] - poi[j][1]) +
               (poi[i][2] - poi[j][2]) * (poi[i][2] - poi[j][2]);
    };
    auto merge = [&](int u, int v) -> int {
        int fu = find(find, u), fv = find(find, v);
        if (fu == fv) return false;
        if (siz[fu] >= siz[fv]) siz[fu] += siz[fv], fa[fv] = fu;
        else
            siz[fv] += siz[fu], fa[fu] = fv;
        return true;
    };
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j) edges.push_back({i, j, calc(i, j)});
    sort(all(edges), [&](const auto& a, const auto& b) { return a[2] < b[2]; });
    for (auto [i, j, v] : edges) {
        merge(i, j);
        if (!--cnt) break;
    }
    for (int i = 0; i < n; ++i) find(find, i);
    map<array<int, 2>, int> cot;
    for (int i = 0; i < n; ++i) cot[{siz[fa[i]], fa[i]}] = -siz[fa[i]];
    if (cot.size() < 3) return -1;
    cout << -next(cot.rbegin(), 0)->second * next(cot.rbegin(), 1)->second * next(cot.rbegin(), 2)->second << '\n';
    return 0;
}

#include <cctype>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <vector>
using namespace std;
#define int long long
#define all(x) (x).begin(), (x).end()
constexpr int inf = numeric_limits<int>::max();
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    string u, v;
    bool judge = false;
    auto calc = [&](const string& s) -> int { return (s[0] - 'a') * 26 * 26 + (s[1] - 'a') * 26 + (s[2] - 'a') + 1; };
    int n = 26 * 26 * 26 + 1;
    vector<vector<int>> edge(n);
    vector<int> in(n), pos;
    while (judge or cin >> u)
        while (true)
            if (cin >> v)
                if (v.find(':') != string::npos) u = v, judge = true;
                else
                    edge[calc(u)].emplace_back(calc(v)), ++in[calc(v)];
            else {
                judge = false;
                break;
            }

    queue<int> que;
    for (int i = 0; i < n; ++i)
        if (not in[i]) que.push(i);
    while (not que.empty()) {
        auto u = que.front();
        que.pop();
        pos.emplace_back(u);
        for (auto& v : edge[u])
            if (--in[v] == 0) que.push(v);
    }
    int s = calc("svr"), t = calc("out"), l = calc("dac"), r = calc("fft"), to;
    vector<array<int, 4>> f(n, {0, 0, 0, 0});
    f[t][0] = 1;
    reverse(all(pos));
    for (auto u : pos)
        for (auto& v : edge[u])
            for (int i = 0; i < 4; ++i) to = i | (u == l ? 1 : 0) | (u == r ? 2 : 0), f[u][to] += f[v][i];
    cout << f[s][3] << '\n';
    return 0;
}

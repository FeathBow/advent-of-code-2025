#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
#define int long long
#define all(x) (x).begin(), (x).end()
constexpr int inf = numeric_limits<int>::max();

auto T(auto& V) {
    int a = inf, b = inf;
    for (auto [x, y] : V) a = min(a, x), b = min(b, y);
    for (auto& v : V) v[0] -= a, v[1] -= b;
    sort(all(V));
    return V;
}

auto get(const auto& V) {
    vector<vector<array<int, 2>>> val;
    for (int bit = 0; bit < 2; ++bit)
        for (int dir = 0; dir < 4; ++dir) {
            vector<array<int, 2>> v;
            for (auto [x, y] : V) {
                if (bit) x = -x;
                for (int _ = 0, t; _ < dir; ++_) t = y, y = -x, x = t;
                v.push_back({x, y});
            }
            val.push_back(T(v));
        }
    return val;
}

bool check(int L, int C, vector<int> cnt, const auto& B, const auto& E) {
    int n = cnt.size(), res = 0;
    for (int i = 0; i < n; ++i) res += cnt[i] * B[i];
    vector<vector<int>> cot(n);
    for (int i = 0; i < n; ++i) {
        if (not cnt[i]) continue;
        vector<int> T;
        for (auto& v : get(E[i])) {
            int X = 0, Y = 0;
            for (auto [x, y] : v) X = max(X, x), Y = max(Y, y);
            int cx = X + 1, cy = Y + 1, val = 0;
            if (cx > L or cy > C) continue;
            for (int j = 0; j + cy <= C; ++j)
                for (int k = 0; k + cx <= L; ++k) {
                    for (auto [x, y] : v) val |= 1ll << ((j + y) * L + (k + x));
                    T.push_back(val), val = 0;
                }
        }
        sort(all(T)), T.erase(unique(all(T)), T.end());
        if (T.empty()) return false;
        cot[i] = move(T);
    }
    auto dfs = [&](auto&& dfs, int v, int res) -> bool {
        if (not res) return true;
        if (res > L * C - __builtin_popcountll(v)) return false;
        int pos = -1, max_ = inf, v_ = 0;
        for (int i = 0; i < n; ++i)
            if (cnt[i]) {
                for (auto m : cot[i])
                    if (not(m & v) and ++v_ >= max_) break;
                if (not v_) return false;
                if (v_ < max_) max_ = v_, pos = i;
            }
        --cnt[pos];
        for (auto m : cot[pos])
            if (not(m & v) and dfs(dfs, v | m, res - B[pos])) return true;
        ++cnt[pos];
        return false;
    };
    return dfs(dfs, 0, res);
}

signed main() {
    cin.tie(0)->sync_with_stdio(false);
    vector<vector<array<int, 2>>> E;
    vector<int> B, D;
    string in, judge;
    while (getline(cin, in)) {
        if (in.empty()) continue;
        if (in.find('x') != string::npos and in.find(':') != string::npos) {
            judge = in;
            break;
        }
        if (in.back() != ':') continue;
        vector<array<int, 2>> poi;
        for (int i = 0; getline(cin, in); ++i) {
            if (in.empty()) break;
            for (int x = 0; x < in.size(); ++x)
                if (in[x] == '#') poi.push_back({x, i});
        }
        poi = T(poi);
        int d = 0;
        for (auto [x, y] : poi) d = max(d, max(x + 1, y + 1));
        E.push_back(poi), B.push_back(poi.size()), D.push_back(d);
    }
    auto solve = [&](const string& in_) -> int {
        auto x = in_.find('x'), c = in_.find(':');
        if (x == string::npos or c == string::npos) return 0;
        int L = stoll(in_.substr(0, x)), C = stoll(in_.substr(x + 1, c - x - 1));
        stringstream ss(in_.substr(c + 1));
        vector<int> cnt(B.size());
        for (int i = 0; i < cnt.size(); ++i)
            if (not(ss >> cnt[i])) cnt[i] = 0;
        int tot = 0, R = 0, P = 0;
        for (int i = 0; i < cnt.size(); ++i) tot += cnt[i], R += cnt[i] * B[i], P = max(P, cnt[i] ? D[i] : 0);
        if (L * C <= 64 and tot <= 12) return check(L, C, cnt, B, E);
        return P and tot <= (L / P) * (C / P);
    };
    int ans = 0;
    if (!judge.empty()) ans += solve(judge);
    while (getline(cin, in))
        if (!in.empty()) ans += solve(in);

    cout << ans << '\n';
    return 0;
}

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define int long long
#define all(x) (x).begin(), (x).end()
constexpr double eps = 1e-7;
constexpr int inf = numeric_limits<int>::max();
auto gauss(auto& mat, auto& cot) {
    int n = mat.size(), m = mat[0].size() - 1, pos = 0;
    fill(all(cot), -1);

    for (int j = 0; j < m and pos < n; ++j) {
        int p = pos;
        for (int i = pos; i < n; ++i)
            if (abs(mat[i][j]) > abs(mat[p][j])) p = i;
        if (abs(mat[p][j]) < eps) continue;
        swap(mat[pos], mat[p]), cot[j] = pos;
        double div = mat[pos][j];
        for (int k = j; k <= m; ++k) mat[pos][k] /= div;
        for (int i = 0; i < n; ++i) {
            if (i == pos) continue;
            double mul = mat[i][j];
            for (int k = j; k <= m; ++k) mat[i][k] -= mat[pos][k] * mul;
        }
        pos++;
    }

    vector<int> check;
    for (int j = 0; j < m; ++j)
        if (cot[j] == -1) check.push_back(j);
    return check;
}

signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int ans = 0;
    string res;
    while (getline(cin, res)) {
        if (res.empty() or res.find('{') == string::npos) continue;
        auto L = res.find('{'), R = res.find('}', L);
        string in = res.substr(L + 1, R - L - 1);
        for (char& c : in)
            if (c == ',') c = ' ';
        stringstream ss(in);
        vector<double> b;
        vector<vector<double>> loc;
        int v, mx = 0;
        while (ss >> v) b.push_back(v), mx = max(mx, v);
        int n = b.size(), p = res.find(']');
        while (true) {
            auto l = res.find('(', p), r = res.find(')', l);
            if (l == string::npos or l > L) break;
            p = r + 1;
            in = res.substr(l + 1, r - l - 1);
            for (char& c : in)
                if (c == ',') c = ' ';
            stringstream ss(in);
            vector<double> tmp(n);
            int x;
            while (ss >> x)
                if (x >= 0 and x < n) tmp[x] = 1.0;
            loc.push_back(tmp);
        }
        int m = loc.size();
        vector<vector<double>> mat(n, vector<double>(m + 1));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) mat[i][j] = loc[j][i];
            mat[i][m] = b[i];
        }

        vector<int> cot(m);
        auto check = gauss(mat, cot);
        int cnt = inf;
        vector<double> x(m);
        auto dfs = [&](auto&& dfs, int u) -> void {
            if (u == check.size()) {
                double sum = 0;
                for (int j = 0; j < m; ++j) {
                    bool judge = false;
                    for (auto v : check)
                        if (v == j) judge = true;
                    double val = 0;
                    if (judge) val = x[j];
                    else {
                        val = mat[cot[j]][m];
                        for (auto v : check) val -= mat[cot[j]][v] * x[v];
                    }
                    if (val < -eps or abs(val - round(val)) > 1e-4) return;
                    int now = (int) round(val);
                    if (now < 0) return;
                    sum += now;
                }
                if (sum < cnt) cnt = (int) sum;
                return;
            }
            for (int j = 0; j <= mx; ++j) {
                x[check[u]] = j;
                double tmp = 0;
                for (int i = 0; i <= u; ++i) tmp += x[check[i]];
                if (tmp >= cnt) break;
                dfs(dfs, u + 1);
            }
        };
        dfs(dfs, 0);
        if (cnt != inf) ans += cnt;
    }
    cout << ans << '\n';
    return 0;
}
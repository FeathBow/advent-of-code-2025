#include <cctype>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
#define int long long
#define all(x) (x).begin(), (x).end()
constexpr int inf = numeric_limits<int>::max();
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int ans = 0;
    string res;
    while (getline(cin, res)) {
        auto L = res.find('['), R = res.find(']', L);
        if (L == string::npos or R == string::npos) continue;
        string in = res.substr(L + 1, R - L - 1);
        int n = in.size();
        int bit = 0, pos = 0;
        for (int i = 0; i < n; ++i)
            if (in[i] == '#') bit |= (1ll << i);
        vector<int> cot, dis(1ll << n, inf);
        dis[0] = 0;
        while (true) {
            auto l = res.find('(', pos), r = res.find(')', l);
            if (l == string::npos or r == string::npos) break;
            pos = r + 1;
            in = res.substr(l + 1, r - l - 1);
            for (char& c : in)
                if (c == ',') c = ' ';
            stringstream ss(in);
            int x, mask = 0;
            while (ss >> x)
                if (0 <= x and x < n) mask ^= (1ll << x);
            if (mask != 0) cot.push_back(mask);
        }
        queue<int> q;
        q.push(0);
        while (not q.empty()) {
            int v = q.front();
            q.pop();
            if (v == bit) break;
            for (auto e : cot)
                if (dis[v ^ e] > dis[v] + 1) dis[v ^ e] = dis[v] + 1, q.push(v ^ e);
        }
        ans += dis[bit];
    }
    cout << ans << '\n';
    return 0;
}

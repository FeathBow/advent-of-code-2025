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
    int x, y;
    char c;
    vector<array<int, 2>> poi;
    while (cin >> x >> c >> y) poi.push_back({x, y});
    int ans = 0;
    for (int i = 0; i < poi.size(); ++i)
        for (int j = i + 1; j < poi.size(); ++j)
            ans = max(ans, abs(poi[i][0] - poi[j][0] + 1) * abs(poi[i][1] - poi[j][1] + 1));
    cout << ans << '\n';
    return 0;
}

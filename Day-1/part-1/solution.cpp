#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define int long long
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int ans = 50, res = 0;
    string s;
    while (cin >> s)
        ans = s[0] == 'R' ? (ans + stoi(s.substr(1))) % 100 : (ans - stoi(s.substr(1)) + 100) % 100, res += ans == 0;
    cout << res << '\n';
    return 0;
}

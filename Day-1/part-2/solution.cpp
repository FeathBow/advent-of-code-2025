#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define int long long
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int ans = 50, res = 0;
    string s;
    while (cin >> s) {
        int judge = ans != 0;
        ans = s[0] == 'R' ? (ans + stoi(s.substr(1))) : (ans - stoi(s.substr(1)));
        if (ans > 0) res += ans / 100, ans %= 100;
        else if (ans < 0)
            res += abs(ans) / 100 + judge, ans = (ans % 100 + 100) % 100;
        else
            ++res;
    }
    cout << res << '\n';
    return 0;
}

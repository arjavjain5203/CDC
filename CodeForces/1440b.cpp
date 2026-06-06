#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> a(n);
        for (int &x : a) cin >> x;

        if (k == 2) {
            bool ok = false;
            for (int x : a) if (x % 2 == 0) ok = true;
            cout << (ok ? 0 : 1) << "\n";
        }

        else if (k == 3 || k == 5) {
            int ans = k;
            for (int x : a) {
                if (x % k == 0) ans = 0;
                else ans = min(ans, k - (x % k));
            }
            cout << ans << "\n";
        }

        else if (k == 4) {
            int cnt2 = 0;

            for (int x : a) {
                if (x % 4 == 0) cnt2 += 2;
                else if (x % 2 == 0) cnt2 += 1;
            }

            if (cnt2 >= 2) {
                cout << 0 << "\n";
            }
            else if (cnt2 == 1) {
                cout << 1 << "\n";
            }
            else {
                int best = 1e9;

                for (int x : a) {
                    int r = x % 4;
                    int cost = (4 - r) % 4;
                    best = min(best, cost);
                }

                cout << min(2, best) << "\n";
            }
        }
    }
}
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        sort(a.rbegin(), a.rend()); // DESCENDING

        vector<int> res;
        vector<bool> possible(20001, false);
        possible[0] = true;

        for (int x : a) {
            if (possible[x]) continue; // would be blocked

            res.push_back(x);

            // update subset sums
            for (int s = 20000; s >= 0; s--) {
                if (possible[s] && s + x <= 20000) {
                    possible[s + x] = true;
                }
            }
        }

        if ((int)res.size() != n) {
            cout << -1 << '\n';
        } else {
            for (int x : res) cout << x << " ";
            cout << '\n';
        }
    }

    return 0;
}
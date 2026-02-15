#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> p(n + 1, -1);
        set<int> unused;
        for (int i = 1; i <= n; i++) unused.insert(i);


        int a = 1;
        int b = a + (n - 1);
        p[n - 1] = a;
        p[n] = b;
        unused.erase(a);
        unused.erase(b);

        for (int i = n - 2; i >= 1; i--) {
            for (int x : unused) {
                if (abs(x - p[i + 1]) % i == 0) {
                    p[i] = x;
                    unused.erase(x);
                    break;
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            cout << p[i] << (i == n ? '\n' : ' ');
        }
    }
    return 0;
}

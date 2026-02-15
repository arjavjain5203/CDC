#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        
        if(n==1)
        {
            cout<<1<<endl;
            continue;
        }
        int j=0;
        int ones = 0;
        for (char c : s) if (c == '1') ones++;

        int res = 0;
        int i = 0;

        while (i < n) {
            if (s[i] == '1') {
                i++;
                continue;
            }
            int j = i;
            while (j < n && s[j] == '0') j++;
            int len = j - i;

            bool left = (i > 0 && s[i - 1] == '1');
            bool right = (j < n && s[j] == '1');

            if (left && right)
                res += (len - 1) / 2;
            else
                res += len / 2;

            i = j;
        }

        cout << ones + res << '\n';
    }
    return 0;
}
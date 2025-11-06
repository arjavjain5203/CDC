#include <bits/stdc++.h>
using namespace std;

int maxFrequencyIndex(const vector<int>& count) {
    int m = count[0];
    int maxi = 0;
    for (int i = 1; i < 26; i++) {
        if (count[i] > m) {
            m = count[i];
            maxi = i;
        }
    }
    return maxi;
}

int count(string s, int k) {
    int n = s.size();
    vector<int> c(26, 0);

    for (int i = 0; i < n; i++) {
        c[s[i] - 'a']++;
    }

    while (k > 0) {
        int temp = maxFrequencyIndex(c);
        c[temp]--;
        k--;
    }

    int sum = 0;
    for (int i = 0; i < 26; i++) {
        if (c[i] != 0) {
            sum += c[i] * c[i];
        }
    }

    return sum;
}

int main() {
    string s;
    cout << "Enter string: ";
    cin >> s;

    int k;
    cout << "Enter integer: ";
    cin >> k;

    cout << count(s, k) << endl;
    return 0;
}

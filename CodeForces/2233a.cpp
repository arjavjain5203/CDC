#include <bits/stdc++.h>
using namespace std;

long long withoutAI(long long n, long long x, long long y)
{
    return (n + x + y - 1) / (x + y);
}

long long withAI(long long n, long long x, long long y, long long z)
{
    long long finish = (n + x - 1) / x;

    if (finish <= z)
        return finish;

    long long rem = n - z * x;
    long long rate = x + 10 * y;

    return z + (rem + rate - 1) / rate;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        long long n, x, y, z;
        cin >> n >> x >> y >> z;

        cout << min(
            withoutAI(n, x, y),
            withAI(n, x, y, z)
        ) << '\n';
    }
}
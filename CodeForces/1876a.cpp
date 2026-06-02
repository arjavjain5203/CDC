#include<bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n, p;
        cin >> n >> p;
        vector<int> travel(n), cost(n);
        for (int i = 0;i < n;i++) cin >> travel[i];
        for (int j = 0;j < n;j++) cin >> cost[j];

        vector<pair<int,int>> match;
        for (int i = 0;i < n;i++)
        {
            match.push_back({ cost[i],travel[i] });
        }

        sort(match.begin(), match.end());
        long long ans = p;
        long long informed = 1; //first guy is informed 

        for (auto [cost, reach] : match)
        {
            if (cost >= p)
            {
                if(informed<n)
                    ans += 1LL*(n - informed) * p;
                break;
            }
            else {
                long long take = min(1LL*reach, n - informed);
                ans += 1LL * take * cost;
                informed += take;
            }

            if (informed >= n) break;
        }

        cout << ans << endl;
    }
    return 0;
}
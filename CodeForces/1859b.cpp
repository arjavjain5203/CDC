#include<bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n,attack;
        cin >> n>>attack;
        vector<vector<int>> nums(n);
        for (int i = 0;i < n;i++)
        {
            int m;
            cin >> m;
            for (int j = 0;j < m;j++)
            {
                int a;
                cin >> a;
                nums[i].push_back(a);
            }
        }
        


        
    }
    return 0;
}
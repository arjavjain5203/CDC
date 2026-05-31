#include <bits/stdc++.h>
using namespace std;

int helper(vector<int>& nums)  // pass by reference
{
    if (nums.empty()) return 0;  // safety check

    sort(nums.begin(), nums.end());

    int sum = 0;
    for (int i : nums)
    {
        sum += i;
    }

    sum *= -1;
    sum += 2 * nums.back();  
    return sum;
}

int main()
{
    int k;
    cin >> k;
    cin.ignore();  

    while (k--)
    {
        string s;
        getline(cin, s);

        stringstream ss(s);
        vector<int> nums;
        int temp;

        while (ss >> temp)
        {
            nums.push_back(temp);
        }

        cout << helper(nums) << endl;
    }

    return 0;
}
#include<bits/stdc++.h>
using namespace std;

int helper(vector<int>&nums,int n)
{
    int res=nums[0]-1;
    for(int i=1;i<n;i++)
    {
        res = gcd(res,(nums[i]-i-1));
    }
    return res;
}

int main()
{
    int t;
    cin>>t;

    while(k--)
    {
        int n;
        cin>>n;
        vector<int> nums;
        for(int i=0;i<n;i++)
            cin>>nums[i];

        cout<<helper(nums,n);
    }
    return 0;
}
#include<bits/stdc++.h>

using namespace std;

void helper(int n,vector<int>&nums,int k)
{
    int sum=0;
    for(int i=0;i<k;i++)
    {
        sum+=nums[i];
    }
    float maxx = (float)sum/k;
    int i=0;
    int j = k-1;
    while(j<n-1)
    {
        sum-=nums[i];
        j++;
        sum+=nums[j];
        i++;
        maxx=max(maxx,(float)sum/k);
    }

    cout<<maxx;
}

int main()
{
    int n;
    cin>>n;
    vector<int>nums(n);
    for(int i=0;i<n;i++)
    {
        cin>>nums[i];
    }
    int k;
    cin>>k;
    helper(n,nums,k);
    return 0;
}
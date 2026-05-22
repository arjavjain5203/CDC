#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin>>n;
    if(n==0)
    {
        cout<<0;
        return 0;
    }
    vector<int>nums(n);
    for(int i=0;i<n;i++)
    {
        cin>>nums[i];
    }
    unordered_map<int,int> freq;
    for(int i : nums)
    {
        freq[i]++;
    }
    int maxx=INT_MIN;
    int mini=INT_MAX;
    for(auto [num,count] : freq)
    {
        maxx=max(maxx,count);
        mini=min(mini,count);
    }
    cout<<maxx<<" "<<mini<<" ";
    cout<<maxx-mini;
    return 0;

}
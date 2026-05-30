
#include<bits/stdc++.h>
using namespace std;



int main()
{
    int k;
    cin>>k;
    while(k--)
    {
        int n;
        cin>>n;
        vector<long long> nums(n);
        for(int i=0;i<n;i++) cin>>nums[i];

        cout<<helper(n,nums)<<endl;
    }
    return 0;
}
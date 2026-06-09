#include<bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,k,q;
        cin>>n>>k>>q;
        vector<int>nums(n);
        for(int i=0;i<n;i++) cin>>nums[i];
        long long res =0;
        int len =0;
        for(int i = 0; i<n;i++)
        {
            if(nums[i]<=q)
            {
                len++;
            }
            else{
                if(len>=k) 
                {
                    res += 1LL*(len-k+1)*(len-k+2)/2;
                }
                len =0;
            }
        }
        if(len>=k) 
        {
            res += 1LL*(len-k+1)*(len-k+2)/2;
        }

        cout<<res<<endl;
    }

    return 0;
}
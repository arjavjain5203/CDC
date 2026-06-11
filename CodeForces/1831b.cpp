#include<bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {

        int n;
        cin >> n;
        vector<int> num1(n);
        vector<int>num2(n);

        for (int i = 0;i < n;i++) cin >> num1[i];
        for (int j = 0;j < n;j++) cin >> num2[j];

        unordered_map<int,int> nums1,nums2;
        int i =0;
        while(i<n)
        {
            int j = i;
            while(j<n && num1[i]==num1[j]) j++;

            nums1[num1[i]] = max(nums1[num1[i]],j-i);
            i=j;
        }
        i=0;
        while(i<n)
        {
            int j = i;
            while(j<n && num2[i]==num2[j]) j++;

            nums2[num2[i]] = max(nums2[num2[i]],j-i);
            i=j;
        }
        int res=INT_MIN;
        for(int i=0;i<=2*n;i++)
        {
            res = max(nums1[i]+nums2[i],res);
        }

        cout<<res<<endl;
    }

    return 0;
}
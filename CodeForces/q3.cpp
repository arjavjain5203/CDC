#include<bits/stdc++.h>
using namespace std;

bool helper(vector<int>nums,int n)
{
    unordered_set<int>s1,s2;
    for(int i=0;i<n;i++)
    {
        cout<<i<<" ";
        int a=s1.size();
        int b=s2.size();
        if(a<b)
        {
            if(s1.find(nums[i])==s1.end())
            {
                s1.insert(nums[i]);
            }
            else if(s2.find(nums[i])==s2.end())
            {
                s2.insert(nums[i]);
            }
            else{
                cout<<"trigger 1"<<" ";
                return false;
            }
        }
        else if(a>b)
        {
            if(s2.find(nums[i])==s2.end())
            {
                s2.insert(nums[i]);
            }
            else if(s1.find(nums[i])==s1.end())
            {
                s1.insert(nums[i]);
            }
            else{
                cout<<"trigger 2"<<" ";
                return false;
            }
        }
        else{
            if(s1.find(nums[i])==s1.end())
            {
                s1.insert(nums[i]);
            }
            else if(s2.find(nums[i])==s2.end())
            {
                s2.insert(nums[i]);
            }
            else{
                cout<<"trigger 3"<<" ";
                return false;
            }
        }
    }

    return s1.size()==s2.size();
}

int main()
{
    int n;
    cin>>n;
    
    if(n%2!=0) {
        cout<<"False";
        return 0;
    }

    vector<int> nums(n);
    for(int i=0;i<n;i++)
    {
        cin>>nums[i];
    }
    cout<<(bool)helper(nums,n);
    return 0;
}
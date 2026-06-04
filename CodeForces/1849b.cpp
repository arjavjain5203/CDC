#include<bits/stdc++.h>
using namespace std;

bool comp(pair<int,int> a, pair<int,int> b)
{
    if(a.first != b.first)
        return a.first > b.first;   // larger remainder first

    return a.second < b.second;     // smaller index first
}

int main()
{
    int k;
    cin>>k;
    while(k--)
    {
        int n,att;
        cin>>n>>att;
        
        vector<int>arr(n);
        vector<pair<int,int>>pos;
        for(int i=0;i<n;i++)
        {
            cin>>arr[i];
            int r =  arr[i]%att;
            pos.push_back({r==0?att:r,i+1});
        }
        sort(pos.begin(),pos.end(),comp); //compare on reminder
        for(auto[value, idx] :pos) cout<<idx<<" ";
        cout<<endl;
    }
    return 0;
}
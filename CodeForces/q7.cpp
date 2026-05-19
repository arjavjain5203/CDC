#include<bits/stdc++.h>
using namespace std;

string helper(string s,string t)
{
    int minlen=INT_MAX;
    int start=-1;
    int m = t.size();
    int n = s.size();
    int count=0,left=0,right=0;
    unordered_map<char,int>freq;
    for(char c : t)
    {
        freq[c]++;
    }
    
    while(right<n )
    {
        if(freq[s[right]]>0)
            count++;
        
        freq[s[right]]--;
        
        while(m==count)
        {
            if( right-left+1<minlen)
            {
                minlen=right-left+1;
                start=left;
            }
            freq[s[left]]++;
            if(freq[s[left]]>0)
            {
                count--;
            }
            left++;
        }
        right++;
    }
    if(count==m)
    {
        if(right-left+1<minlen)
            {
                minlen=right-left+1;
                start=left;
            }
    }
    return s.substr(start,minlen);
}

int main()
{
    string s,t;
    cin>>s;
    cin>>t;

    cout<<helper(s,t);

    return 0;
}
#include<bits/stdc++.h>
using namespace std;

void helper(string &s)
{
    map<char,int> mapping; //num->count
    
    int  maxcount=0;

    for(char i : s)
    {
        if(i>='0' && i<='9')
            {
                mapping[i]++;
                maxcount=max(maxcount,mapping[i]);
            }
    }
    for(auto [digit,count] : mapping )
    {
        if(count>=maxcount)
        {
            cout<<digit<<" ";
        }
    }
}


int main()
{
    string s;
    getline(cin,s);
    helper(s);
    return 0;
}
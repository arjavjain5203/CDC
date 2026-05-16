#include<string>
#include<iostream>
using namespace std;

int helper(string s)
{
    int upper=0,lower=0;
    for(char c : s)
    {
        if(c<='Z' && c>='a') lower++;
        else upper++;
    }
    return abs(upper-lower);
}

int main()
{
    string s;
    cin>>s;
    cout<<helper(s);
    return 0;
}
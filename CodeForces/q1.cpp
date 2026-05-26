#include<string>
#include<iostream>
using namespace std;

int helper(string s)
{
    int upper=0,lower=0;
    for(char c : s)
    {
        if(c<='z' && c>='a') lower++;
        else upper++;
    }
    cout << upper << endl << lower << endl;
    return min(upper,lower);
}

int main()
{
    string s;
    cin>>s;
    cout<<helper(s);
    return 0;
}
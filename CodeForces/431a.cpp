#include<bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> costs(4);
    for(int i=0;i<4;i++)
    {
        cin>>costs[i];
    }
    string str;
    int cost=0;
    cin>>str;
    for(char c : str)
    {
        if(c=='1') cost+=costs[0];
        else if(c=='2') cost+=costs[1];
        else if(c=='3') cost+=costs[2];
        else cost+=costs[3];
    }

    cout<<cost<<endl;
    return 0;
}
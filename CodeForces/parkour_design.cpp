#include<bits/stdc++.h>
using namespace std;

// (xi,yi)→(xi+2,yi+1)
// ;
// (xi,yi)→(xi+3,yi)
// ;
// (xi,yi)→(xi+4,yi−1)
// .


bool helper(int xi,int yi,int xf,int yf)
{
    if(xi==xf && yi==yf) return true;

    if(xi>xf || yi>yf) return false;

    if(helper(xi+2,yi+1,xf,yf)) return true;
    if(helper(xi+3,yi,xf,yf)) return true;
    if(helper(xi+4,yi-1,xf,yf)) return true;

    return false;
}


int main()
{
    int k;
    cin>>k;
    while(k--)
    {
        int a,b;
        cin>>a>>b;
        
        cout<<helper(0,0,a,b);
    }
    return 0;
}
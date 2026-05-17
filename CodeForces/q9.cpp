#include<bits/stdc++.h>
using namespace std;

void helper(int n , int m,vector<int>&num1,vector<int>&num2)
{
    int i = n-1;
    int j = m-1;
    int k = m+n-1;
    while(  i>0   &&  j>0   )
    {
        if(num1[i]>num2[j])
        {
            num1[k]=num1[i];
            k--;
            i--;
        }
        else{
            num1[k]=num2[j];
            k--;
            j--;
        }
    }
    while(i>0)
    {
        num1[k]=num1[i];
            k--;
            i--;        
    }
    while(j>0)
    {
        num1[k]=num2[j];
            k--;
            j--;
    }
}

int main()
{
    int m,n;
    cin>>n>>m;
    vector<int>num1(m+n,0),num2(n);
    
    for(int i=0;i<m+n;i++)
    {
        cin>>num1[i];
    }
    for(int i=0;i<m;i++)
    {
        cin>>num2[i];
    }

    helper(n,m,num1,num2);

    for(int i : num1)
        cout<<i;
    return 0;

}
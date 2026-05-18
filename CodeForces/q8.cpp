#include<bits/stdc++.h>
using namespace std;

bool helper(string s)
{
    stack<char>st;
    for(char c : s)
    {
        if(c=='('||c=='{'||c=='[')
        {
            st.push(c);
        }
        else{
            if( c== ')' && st.top()=='(')
            {
                st.pop();
            }
            else if( c== ']' && st.top()=='[')
            {
                st.pop();
            }
            else if( c== '}' && st.top()=='{')
            {
                st.pop();
            }
            else{
                return false;
            }
        }
    }
    return st.empty();
}

int main()
{
    string s;
    cin>>s;
    cout<<helper(s);
    return 0;
}
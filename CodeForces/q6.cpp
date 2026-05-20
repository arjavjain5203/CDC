#include<bits/stdc++.h>
using namespace std;

void helper(vector<vector<int>> &grid,int n,int m,int sr,int sc,int colour)
{
    int initial = grid[sr][sc];
    if(initial==colour) {
        return;
    }
    queue<pair<int,int>>q;
    q.push({sr,sc});
    while(!q.empty())
    {
        auto [x,y] = q.front();
        q.pop();
        
        vector<vector<int>> valid={
            {0,1},{1,0},{-1,0},{0,-1}
        };
        for(int i=0;i<4;i++)
        {
            int tx=valid[i][0];
            int ty=valid[i][1];
            int nx=x+tx;
            int ny=y+ty;

            if(nx>=0 && nx<n && ny>=0 && ny<m)
            {
                if(grid[nx][ny]==initial)
                {
                    q.push({nx,ny});
                    grid[nx][ny]=colour;
                }
            }

        }
    }


}

int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<int>> grid(n,vector<int>(m));
 
     for(int i=0;i<n;i++)
     {
         for(int j=0;j<m;j++)
         {
             cin>>grid[i][j];
         }

     }

    int sr,sc,colour;
    cin>>sr>>sc>>colour;
    helper(grid,n,m,sr,sc,colour);

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;

}

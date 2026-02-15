#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <climits>
#include <functional>
using namespace std;

struct Interval { int a,b; };
void add_interval(map<int, vector<Interval>>& mp, int key, int a, int b){
    if(a>b) swap(a,b);
    mp[key].push_back({a,b});
}
void normalize(map<int, vector<Interval>>& mp){
    for(auto &p: mp){
        auto &v = p.second;
        sort(v.begin(), v.end(), [](const Interval& x, const Interval& y){
            if(x.a!=y.a) return x.a<y.a;
            return x.b<y.b;
        });
        vector<Interval> out;
        for(auto &it: v){
            if(out.empty() || it.a>out.back().b) out.push_back(it);
            else out.back().b = max(out.back().b, it.b);
        }
        v.swap(out);
    }
}
bool covers(const map<int, vector<Interval>>& mp, int key, int a, int b){
    auto it = mp.find(key);
    if(it==mp.end()) return false;
    for(auto &iv: it->second) if(iv.a<=a && iv.b>=b) return true;
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    if(!(cin>>n>>m)) return 0;
    int N;
    cin>>N;
    map<int, vector<Interval>> vert, hor;
    for(int i=0;i<N;i++){
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        if(x1!=x2 && y1!=y2){ cout<<"Invalid\n"; return 0; }
        if(x1==x2){
            if(x1<0 || x1>n){ cout<<"Invalid\n"; return 0; }
            add_interval(vert, x1, y1, y2);
        } else {
            if(y1<0 || y1>m){ cout<<"Invalid\n"; return 0; }
            add_interval(hor, y1, x1, x2);
        }
    }
    normalize(vert);
    normalize(hor);
    set<int> xs, ys;
    xs.insert(0); xs.insert(n);
    ys.insert(0); ys.insert(m);
    for(auto &p: vert) xs.insert(p.first);
    for(auto &p: hor) ys.insert(p.first);
    for(auto &p: hor) for(auto &iv: p.second){ xs.insert(iv.a); xs.insert(iv.b); }
    for(auto &p: vert) for(auto &iv: p.second){ ys.insert(iv.a); ys.insert(iv.b); }
    vector<int> xv(xs.begin(), xs.end()), yv(ys.begin(), ys.end());
    int cols = (int)xv.size()-1, rows = (int)yv.size()-1;
    if(rows<=0 || cols<=0){ cout<<"Invalid\n"; return 0; }
    vector<vector<bool>> vwall(rows, vector<bool>(cols+1,false));
    vector<vector<bool>> hwall(rows+1, vector<bool>(cols,false));
    for(int r=0;r<rows;r++){
        int ya=yv[r], yb=yv[r+1];
        for(int c=0;c<=cols;c++){
            int xline=xv[c];
            if(xline==0 || xline==n) vwall[r][c]=true;
            else if(covers(vert, xline, ya, yb)) vwall[r][c]=true;
        }
    }
    for(int r=0;r<=rows;r++){
        int yline=yv[r];
        for(int c=0;c<cols;c++){
            int xa=xv[c], xb=xv[c+1];
            if(yline==0 || yline==m) hwall[r][c]=true;
            else if(covers(hor, yline, xa, xb)) hwall[r][c]=true;
        }
    }
    vector<vector<int>> comp(rows, vector<int>(cols, -1));
    int compCnt=0;
    for(int i=0;i<rows;i++) for(int j=0;j<cols;j++){
        if(comp[i][j]!=-1) continue;
        queue<pair<int,int>> q;
        comp[i][j]=compCnt;
        q.push({i,j});
        while(!q.empty()){
            auto p=q.front(); q.pop();
            int r=p.first,c=p.second;
            if(r>0 && !hwall[r][c] && comp[r-1][c]==-1){ comp[r-1][c]=compCnt; q.push({r-1,c}); }
            if(r<rows-1 && !hwall[r+1][c] && comp[r+1][c]==-1){ comp[r+1][c]=compCnt; q.push({r+1,c}); }
            if(c>0 && !vwall[r][c] && comp[r][c-1]==-1){ comp[r][c-1]=compCnt; q.push({r,c-1}); }
            if(c<cols-1 && !vwall[r][c+1] && comp[r][c+1]==-1){ comp[r][c+1]=compCnt; q.push({r,c+1}); }
        }
        compCnt++;
    }
    struct Rect { int rmin,rmax,cmin,cmax,cnt; Rect(){ rmin=INT_MAX; rmax=INT_MIN; cmin=INT_MAX; cmax=INT_MIN; cnt=0; } };
    vector<Rect> comps(compCnt);
    for(int r=0;r<rows;r++) for(int c=0;c<cols;c++){
        int id=comp[r][c];
        comps[id].rmin=min(comps[id].rmin,r);
        comps[id].rmax=max(comps[id].rmax,r);
        comps[id].cmin=min(comps[id].cmin,c);
        comps[id].cmax=max(comps[id].cmax,c);
        comps[id].cnt++;
    }
    for(int id=0;id<compCnt;id++){
        for(int r=comps[id].rmin;r<=comps[id].rmax;r++){
            for(int c=comps[id].cmin;c<=comps[id].cmax;c++){
                if(r<0||r>=rows||c<0||c>=cols||comp[r][c]!=id){ cout<<"Invalid\n"; return 0; }
            }
        }
    }
    vector<pair<int,int>> edges;
    int nextDummy = compCnt;
    for(int r=0;r<rows;r++){
        for(int c=0;c<=cols;c++){
            if(!vwall[r][c]) continue;
            int left = (c-1>=0)? comp[r][c-1]: -1;
            int right = (c<cols)? comp[r][c]: -1;
            if(left!=-1 && right!=-1){
                if(left==right) continue;
                edges.push_back({left,right});
            } else if(left!=-1){
                edges.push_back({left,nextDummy});
                nextDummy++;
            } else if(right!=-1){
                edges.push_back({right,nextDummy});
                nextDummy++;
            }
        }
    }
    for(int r=0;r<=rows;r++){
        for(int c=0;c<cols;c++){
            if(!hwall[r][c]) continue;
            int top = (r-1>=0)? comp[r-1][c]: -1;
            int bot = (r<rows)? comp[r][c]: -1;
            if(top!=-1 && bot!=-1){
                if(top==bot) continue;
                edges.push_back({top,bot});
            } else if(top!=-1){
                edges.push_back({top,nextDummy});
                nextDummy++;
            } else if(bot!=-1){
                edges.push_back({bot,nextDummy});
                nextDummy++;
            }
        }
    }
    int V = nextDummy;
    vector<int> parity(V, -1);
    for(int i=0;i<compCnt;i++) parity[i] = (comps[i].rmin + comps[i].cmin) & 1;
    for(auto &e: edges){
        int u=e.first, v=e.second;
        if(parity[u]==-1){
            cout<<"Invalid\n"; return 0;
        }
        if(v<compCnt){
            if(parity[v]==-1){ cout<<"Invalid\n"; return 0; }
            if(parity[u]==parity[v]){ cout<<"Invalid\n"; return 0; }
        } else {
            parity[v] = 1 - parity[u];
        }
    }
    for(int i=compCnt;i<V;i++) if(parity[i]==-1) parity[i]=0;
    vector<int> leftIndex(V,-1), rightIndex(V,-1);
    int L=0,Rg=0;
    for(int i=0;i<V;i++){
        if(parity[i]==0) leftIndex[i]=L++;
        else rightIndex[i]=Rg++;
    }
    vector<vector<int>> G(L);
    for(auto &e: edges){
        int u=e.first, v=e.second;
        int a=u, b=v;
        if(parity[a]==1) swap(a,b);
        if(parity[a]!=0 || parity[b]!=1){ cout<<"Invalid\n"; return 0; }
        G[leftIndex[a]].push_back(rightIndex[b]);
    }
    vector<int> pairU(L, -1), pairV(Rg, -1), dist(L);
    auto bfs = [&]()->bool{
        queue<int> q;
        for(int u=0;u<L;u++){
            if(pairU[u]==-1){ dist[u]=0; q.push(u); }
            else dist[u]=-1;
        }
        bool reachable=false;
        while(!q.empty()){
            int u=q.front(); q.pop();
            for(int v: G[u]){
                int pu = pairV[v];
                if(pu!=-1 && dist[pu]==-1){ dist[pu]=dist[u]+1; q.push(pu); }
                if(pu==-1) reachable=true;
            }
        }
        return reachable;
    };
    function<bool(int)> dfs = [&](int u)->bool{
        for(int v: G[u]){
            int pu = pairV[v];
            if(pu==-1 || (dist[pu]==dist[u]+1 && dfs(pu))){
                pairU[u]=v; pairV[v]=u; return true;
            }
        }
        dist[u]=-1;
        return false;
    };
    int matching=0;
    while(bfs()){
        for(int u=0;u<L;u++) if(pairU[u]==-1) if(dfs(u)) matching++;
    }
    int minEdgeCover = V - matching;
    cout<<minEdgeCover<<"\n";
    return 0;
}

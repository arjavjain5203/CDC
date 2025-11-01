#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    if(!(cin >> N >> M)) return 0;
    vector<string> grid(N);
    for (int i = 0; i < N; ++i){
      
        string s;
     
        vector<string> tokens;
        while ((int)tokens.size() < M && cin >> s) {
            if ((int)s.size() == 1) tokens.push_back(s);
            else if ((int)s.size() == M) { 
                tokens.clear();
                for (char c: s) {
                    string t(1,c);
                    tokens.push_back(t);
                }
                break;
            } else {
                     if ((int)s.size() == M) {
                    tokens.clear();
                    for (char c: s) tokens.push_back(string(1,c));
                    break;
                } else {
                  
                    for (char c: s) {
                        tokens.push_back(string(1,c));
                        if ((int)tokens.size() == M) break;
                    }
                }
            }
        }

        string row="";
        for (int j=0;j<M;j++) row.push_back(tokens[j][0]);
        grid[i] = row;
    }


    vector<int> rowRod(N,0), colRod(M,0);
    for (int i=0;i<N;i++){
        bool allNonDot=true;
        for (int j=0;j<M;j++) if (grid[i][j]=='.') { allNonDot=false; break; }
        if (allNonDot) rowRod[i]=1;
    }
    for (int j=0;j<M;j++){
        bool allNonDot=true;
        for (int i=0;i<N;i++) if (grid[i][j]=='.') { allNonDot=false; break; }
        if (allNonDot) colRod[j]=1;
    }

    vector<vector<int>> cable(N, vector<int>(M,0));
    deque<pair<int,int>> dq;
    for (int i=0;i<N;i++){
        if (grid[i][0]=='C') { cable[i][0]=1; dq.emplace_back(i,0); }
        if (grid[i][M-1]=='C') { cable[i][M-1]=1; dq.emplace_back(i,M-1); }
    }
    for (int j=0;j<M;j++){
        if (grid[0][j]=='C') { cable[0][j]=1; dq.emplace_back(0,j); }
        if (grid[N-1][j]=='C') { cable[N-1][j]=1; dq.emplace_back(N-1,j); }
    }
    const int di[4] = {-1,1,0,0}, dj[4]={0,0,-1,1};
    while(!dq.empty()){
        auto p = dq.front(); dq.pop_front();
        int i=p.first, j=p.second;
        for (int d=0; d<4; ++d){
            int ni=i+di[d], nj=j+dj[d];
            if (ni<0||ni>=N||nj<0||nj>=M) continue;
            if (grid[ni][nj]=='.') continue;
            if (cable[ni][nj]) continue;
         
            if (grid[i][j]=='C' || grid[ni][nj]=='C'){
                cable[ni][nj]=1;
                dq.emplace_back(ni,nj);
            }
        }
    }

    bool anyCable=false;
    for (int i=0;i<N;i++) for (int j=0;j<M;j++) if (cable[i][j]) anyCable=true;
    if (!anyCable) { cout << 0 << "\n"; return 0; }

    vector<int> rowIndex(N,-1), colIndex(M,-1);
    int Rcount=0;
    for (int i=0;i<N;i++) if (rowRod[i]) rowIndex[i]=Rcount++;
    for (int j=0;j<M;j++) if (colRod[j]) colIndex[j]=Rcount++;

      vector<int> parity(Rcount,0);
    struct Cross { int a,b; }; 
    vector< tuple<int,int,int> > crosses; 
    bool needsDummy=false;
    vector<vector<int>> graph(Rcount); 
    vector<pair<int,int>> crossCells; 
    vector<int> crossU, crossV; 
    for (int i=0;i<N;i++){
        for (int j=0;j<M;j++){
            if (!cable[i][j]) continue;
            bool hasRow = rowRod[i];
            bool hasCol = colRod[j];
            if (!hasRow && !hasCol) continue; 
            int u = -1, v = -1;
            if (hasRow) u = rowIndex[i];
            if (hasCol) v = colIndex[j];
            if (u!=-1) {
                if (grid[i][j]=='R') parity[u] ^= 1; 
            }
            if (v!=-1) {
                if (grid[i][j]=='R') parity[v] ^= 1;
            }
            if (u!=-1 && v!=-1) {
                graph[u].push_back(v);
                graph[v].push_back(u);
                crossU.push_back(u); crossV.push_back(v);
                crossCells.emplace_back(i,j);
            } else {
                needsDummy = true;
                crossU.push_back(u==-1?v:u);
                crossV.push_back(-1);
                crossCells.emplace_back(i,j);
            }
        }
    }

    if (Rcount==0) { cout << 0 << "\n"; return 0; }

    int dummyIdx = -1;
    if (needsDummy) {
        dummyIdx = Rcount;
        graph.push_back({});
        parity.push_back(0);
        ++Rcount;
    }

    for (size_t k=0;k<crossU.size();++k){
        int u = crossU[k], v = crossV[k];
        if (v==-1){
            if (dummyIdx==-1) {
                continue;
            }
            graph[u].push_back(dummyIdx);
            graph[dummyIdx].push_back(u);
        }
    }
 vector<int> comp(Rcount, -1);
    int compCnt = 0;
    for (int v=0; v<Rcount; ++v){
        if (comp[v]!=-1) continue;
           deque<int> q; q.push_back(v); comp[v]=compCnt;
        while(!q.empty()){
            int x=q.front(); q.pop_front();
            for (int y: graph[x]){
                if (comp[y]==-1){ comp[y]=compCnt; q.push_back(y); }
            }
        }
        compCnt++;
    }

    long long answer = 0;
    for (int c=0; c<compCnt; ++c){
        vector<int> nodes;
        for (int v=0; v<Rcount; ++v) if (comp[v]==c) nodes.push_back(v);
      
        vector<int> Tnodes;
        for (int v: nodes) if (parity[v]) Tnodes.push_back(v);
        if (Tnodes.empty()) continue;
        int S = nodes.size();
        unordered_map<int,int> idxMap; 
        for (int i=0;i<S;i++) idxMap[nodes[i]] = i;
        vector<vector<int>> dist(S, vector<int>(S, INT_MAX));
        for (int i=0;i<S;i++){
            int src = nodes[i];
            deque<int> q; q.push_back(src);
            vector<int> d(Rcount, -1);
            d[src]=0;
            while(!q.empty()){
                int x=q.front(); q.pop_front();
                for (int y: graph[x]){
                    if (d[y]==-1){ d[y]=d[x]+1; q.push_back(y); }
                }
            }
            for (int j=0;j<S;j++){
                if (d[nodes[j]]>=0) dist[i][j]=d[nodes[j]];
            }
        }
        int t = Tnodes.size();
        if (t % 2 == 1) {
            cout << -1 << "\n";
            return 0;
        }
        vector<int> Tloc;
        for (int v: Tnodes) Tloc.push_back(idxMap[v]);

        if (t == 0) continue;
        if (t > 22) {
            vector<int> used(t,0);
            long long sum=0;
            for (int a=0;a<t;a++){
                if (used[a]) continue;
                int best=-1, bestd=INT_MAX, bi=-1;
                for (int b=a+1;b<t;b++){
                    if (used[b]) continue;
                    int da = dist[Tloc[a]][Tloc[b]];
                    if (da < bestd){ bestd = da; best = b; }
                }
                if (best==-1){ cout << -1 << "\n"; return 0; }
                used[a]=used[best]=1;
                sum += bestd;
            }
            answer += sum;
            continue;
        }

    
        int FULL = 1<<t;
        const long long INF = (1LL<<60);
        vector<long long> dp(FULL, INF);
        dp[0]=0;
        for (int mask=0; mask<FULL; ++mask){
            if (dp[mask] == INF) continue;
            int first = -1;
            for (int i=0;i<t;i++) if (!(mask & (1<<i))) { first = i; break; }
            if (first==-1) continue;
            for (int j=first+1;j<t;j++){
                if (mask & (1<<j)) continue;
                int u = Tloc[first], v2 = Tloc[j];
                int dcost = dist[u][v2];
                if (dcost==INT_MAX) continue; 
                int nmask = mask | (1<<first) | (1<<j);
                dp[nmask] = min(dp[nmask], dp[mask] + dcost);
            }
        }
        long long best = dp[FULL-1];
        if (best >= INF/2) { cout << -1 << "\n"; return 0; }
        answer += best;
    }

    cout << answer << "\n";
    return 0;
}

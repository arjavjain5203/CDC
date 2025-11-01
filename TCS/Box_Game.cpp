#include <bits/stdc++.h>
using namespace std;

struct Cubie {
    array<char,6> s;
    Cubie(){ s.fill('\0'); }
};

int N, K;

const array<array<int,3>,6> faceNormal = {{
    {0, +1, 0},
    {0, 0, +1},
    {0, -1, 0},
    {0, 0, -1},
    {-1,0, 0},
    {+1,0, 0}
}};

int faceIndexByNormal(const array<int,3>& v){
    for(int f=0; f<6; ++f){
        if(faceNormal[f][0]==v[0] && faceNormal[f][1]==v[1] && faceNormal[f][2]==v[2]) return f;
    }
    return -1;
}

array<int,3> rotXpos(const array<int,3>& v){ return { v[0], -v[2], v[1] }; }
array<int,3> rotXneg(const array<int,3>& v){ return { v[0], v[2], -v[1] }; }
array<int,3> rotYpos(const array<int,3>& v){ return { v[2], v[1], -v[0] }; }
array<int,3> rotYneg(const array<int,3>& v){ return { -v[2], v[1], v[0] }; }
array<int,3> rotZpos(const array<int,3>& v){ return { -v[1], v[0], v[2] }; }
array<int,3> rotZneg(const array<int,3>& v){ return { v[1], -v[0], v[2] }; }

inline tuple<int,int,int> coord_rotXpos(int x,int y,int z){ return {x, N-1 - z, y}; }
inline tuple<int,int,int> coord_rotXneg(int x,int y,int z){ return {x, z, N-1 - y}; }
inline tuple<int,int,int> coord_rotYpos(int x,int y,int z){ return {z, y, N-1 - x}; }
inline tuple<int,int,int> coord_rotYneg(int x,int y,int z){ return {N-1 - z, y, x}; }
inline tuple<int,int,int> coord_rotZpos(int x,int y,int z){ return {N-1 - y, x, z}; }
inline tuple<int,int,int> coord_rotZneg(int x,int y,int z){ return {y, N-1 - x, z}; }

struct Cube {
    vector<Cubie> cells;
    Cube(){ cells.assign(N*N*N, Cubie()); }
    inline Cubie & at(int x,int y,int z){ return cells[(x*N + y)*N + z]; }
    inline const Cubie & atc(int x,int y,int z) const { return cells[(x*N + y)*N + z]; }
    inline const Cubie & atc(int x,int y,int z) const { return cells[(x*N + y)*N + z]; }
    Cube copy() const { Cube c; c.cells = cells; return c; }

    void rotate_layer(char axis, int layerIndex, int dir){
        vector<Cubie> newCells = cells;
        auto idx = [&](int x,int y,int z){ return (x*N + y)*N + z; };

        for(int x=0;x<N;++x) for(int y=0;y<N;++y) for(int z=0;z<N;++z){
            bool inLayer = (axis=='X' && x==layerIndex) || (axis=='Y' && y==layerIndex) || (axis=='Z' && z==layerIndex);
            if(!inLayer) continue;

            int nx, ny, nz;

            if(axis=='X'){
                if(dir==+1) tie(nx,ny,nz) = coord_rotXpos(x,y,z);
                else tie(nx,ny,nz) = coord_rotXneg(x,y,z);
            } else if(axis=='Y'){
                if(dir==+1) tie(nx,ny,nz) = coord_rotYpos(x,y,z);
                else tie(nx,ny,nz) = coord_rotYneg(x,y,z);
            } else {
                if(dir==+1) tie(nx,ny,nz) = coord_rotZpos(x,y,z);
                else tie(nx,ny,nz) = coord_rotZneg(x,y,z);
            }

            Cubie tmp; tmp.s.fill('\0');

            for(int f=0; f<6; ++f){
                char ch = at(x,y,z).s[f];
                if(ch=='\0') continue;
                array<int,3> norm = faceNormal[f];
                array<int,3> norm2;
                if(axis=='X') norm2 = (dir==+1? rotXpos(norm) : rotXneg(norm));
                else if(axis=='Y') norm2 = (dir==+1? rotYpos(norm) : rotYneg(norm));
                else norm2 = (dir==+1? rotZpos(norm) : rotZneg(norm));
                int fNew = faceIndexByNormal(norm2);
                if(fNew<0) continue;
                tmp.s[fNew] = ch;
            }

            newCells[idx(nx,ny,nz)] = tmp;
        }

        cells.swap(newCells);
    }

    void rotate_whole_cube(char axis, int dir){
        vector<Cubie> newCells = cells;
        auto idx = [&](int x,int y,int z){ return (x*N + y)*N + z; };

        for(int x=0;x<N;++x) for(int y=0;y<N;++y) for(int z=0;z<N;++z){
            int nx, ny, nz;
            if(axis=='X'){
                if(dir==+1) tie(nx,ny,nz) = coord_rotXpos(x,y,z);
                else tie(nx,ny,nz) = coord_rotXneg(x,y,z);
            } else if(axis=='Y'){
                if(dir==+1) tie(nx,ny,nz) = coord_rotYpos(x,y,z);
                else tie(nx,ny,nz) = coord_rotYneg(x,y,z);
            } else {
                if(dir==+1) tie(nx,ny,nz) = coord_rotZpos(x,y,z);
                else tie(nx,ny,nz) = coord_rotZneg(x,y,z);
            }

            Cubie tmp; tmp.s.fill('\0');
            for(int f=0; f<6; ++f){
                char ch = at(x,y,z).s[f];
                if(ch=='\0') continue;
                array<int,3> norm = faceNormal[f];
                array<int,3> norm2;
                if(axis=='X') norm2 = (dir==+1? rotXpos(norm) : rotXneg(norm));
                else if(axis=='Y') norm2 = (dir==+1? rotYpos(norm) : rotYneg(norm));
                else norm2 = (dir==+1? rotZpos(norm) : rotZneg(norm));
                int fNew = faceIndexByNormal(norm2);
                tmp.s[fNew] = ch;
            }
            newCells[idx(nx,ny,nz)] = tmp;
        }
        cells.swap(newCells);
    }

    vector<string> extractFace(int faceId) const {
        vector<string> res(N, string(N, '.'));
        for(int i=0;i<N;++i) for(int j=0;j<N;++j){
            int x,y,z;
            if(faceId==3){ x=j; y=i; z=0; }
            else if(faceId==1){ x=N-1-j; y=i; z=N-1; }
            else if(faceId==2){ x=j; y=0; z=N-1-i; }
            else if(faceId==0){ x=j; y=N-1; z=i; }
            else if(faceId==4){ x=0; y=i; z=N-1-j; }
            else { x=N-1; y=i; z=j; }
            char c = atc(x,y,z).s[faceId];
            res[i][j] = (c==0? '.' : c);
        }
        return res;
    }

    bool anyFaceSolved() const {
        for(int f=0; f<6; ++f){
            char first = 0;
            bool ok = true;
            for(int i=0;i<N && ok;++i) for(int j=0;j<N;++j){
                int x,y,z;
                if(f==3){ x=j; y=i; z=0; }
                else if(f==1){ x=N-1-j; y=i; z=N-1; }
                else if(f==2){ x=j; y=0; z=N-1-i; }
                else if(f==0){ x=j; y=N-1; z=i; }
                else if(f==4){ x=0; y=i; z=N-1-j; }
                else { x=N-1; y=i; z=j; }
                char c = atc(x,y,z).s[f];
                if(c==0){ ok=false; break; }
                if(!first) first=c;
                else if(c!=first) { ok=false; break; }
            }
            if(ok) return true;
        }
        return false;
    }
};

Cube buildCubeFromFaces(const vector<vector<string>>& faces){
    Cube C;
    for(int f=0; f<6; ++f){
        for(int i=0;i<N;++i) for(int j=0;j<N;++j){
            char ch = faces[f][i][j];
            int x,y,z;
            if(f==3){ x=j; y=i; z=0; }
            else if(f==1){ x=N-1-j; y=i; z=N-1; }
            else if(f==2){ x=j; y=0; z=N-1-i; }
            else if(f==0){ x=j; y=N-1; z=i; }
            else if(f==4){ x=0; y=i; z=N-1-j; }
            else { x=N-1; y=i; z=j; }
            C.at(x,y,z).s[f] = ch;
        }
    }
    return C;
}

struct Instr {
    string raw;
    bool isGlobal;
    string side;
    int k;
    string dir;
};

Instr parseInstrLine(const string& line){
    Instr ins; ins.raw = line; ins.isGlobal = false; ins.side=""; ins.k=0; ins.dir="";
    string s = line;
    for(auto &c:s) if(c>='A' && c<='Z') c = char(c - 'A' + 'a');
    stringstream ss(s);
    vector<string> tok;
    string w;
    while(ss>>w) tok.push_back(w);
    if(tok.size()==2){
        if(tok[0]=="turn" || tok[0]=="rotate"){
            ins.isGlobal = true;
            ins.raw = line;
        }
    } else if(tok.size()==3){
        ins.isGlobal = false;
        ins.side = tok[0];
        ins.k = stoi(tok[1]);
        ins.dir = tok[2];
    } else if(tok.size()==4){
        if(tok[0]=="turn" || tok[0]=="rotate"){
            ins.isGlobal = true;
        } else {
            ins.side = tok[0];
            ins.k = stoi(tok[1]);
            ins.dir = tok[2];
        }
    } else {
        string low = s;
        if(low.find("turn")!=string::npos || low.find("rotate")!=string::npos){
            ins.isGlobal = true;
        } else {
            if(tok.size()>=3){
                ins.side = tok[0];
                ins.k = stoi(tok[1]);
                ins.dir = tok[2];
            }
        }
    }
    ins.raw = line;
    return ins;
}

int sideNameToFace(const string& name){
    string s = name;
    for(auto &c:s) if(c>='A' && c<='Z') c = char(c - 'A' + 'a');
    if(s=="base" || s=="down" || s=="d") return 0;
    if(s=="back") return 1;
    if(s=="top" || s=="up" || s=="u") return 2;
    if(s=="front") return 3;
    if(s=="left" || s=="l") return 4;
    if(s=="right" || s=="r") return 5;
    return -1;
}

using Move = pair<char,int>;
vector<vector<Move>> orientSeqToFront(6);
vector<vector<Move>> orientSeqFromFront(6);

array<int,6> permFacesForWholeCube(char axis, int dir){
    array<int,6> perm;
    for(int pos=0; pos<6; ++pos){
        array<int,3> n = faceNormal[pos];
        array<int,3> n2;
        if(axis=='X') n2 = (dir==+1? rotXpos(n) : rotXneg(n));
        else if(axis=='Y') n2 = (dir==+1? rotYpos(n) : rotYneg(n));
        else n2 = (dir==+1? rotZpos(n) : rotZneg(n));
        int newPos = faceIndexByNormal(n2);
        perm[pos] = newPos;
    }
    return perm;
}

array<int,6> applyPerm(const array<int,6>& cur, const array<int,6>& perm){
    array<int,6> nxt;
    for(int p=0;p<6;++p){
        int newPos = perm[p];
        nxt[newPos] = cur[p];
    }
    return nxt;
}

void precomputeOrientations(){
    array<int,6> start;
    for(int i=0;i<6;++i) start[i]=i;
    map<array<int,6>, vector<Move>> seq;
    queue<array<int,6>>q;
    seq[start] = {};
    q.push(start);

    vector<pair<char,int>> ops = {{'X',+1},{'X',-1},{'Y',+1},{'Y',-1},{'Z',+1},{'Z',-1}};

    while(!q.empty()){
        auto cur = q.front(); q.pop();
        auto curSeq = seq[cur];
        for(int origFace=0; origFace<6; ++origFace){
            int pos=-1;
            for(int p=0;p<6;++p) if(cur[p]==origFace) { pos=p; break; }
            if(pos==3 && orientSeqToFront[origFace].empty()){
                orientSeqToFront[origFace] = curSeq;
                vector<Move> inv;
                for(int i=(int)curSeq.size()-1;i>=0;--i){
                    auto mv = curSeq[i];
                    inv.push_back({mv.first, -mv.second});
                }
                orientSeqFromFront[origFace] = inv;
            }
        }
        for(auto op: ops){
            auto perm = permFacesForWholeCube(op.first, op.second);
            auto nxt = applyPerm(cur, perm);
            if(!seq.count(nxt)){
                auto s = curSeq;
                s.push_back(op);
                seq[nxt]=s;
                q.push(nxt);
            }
        }
    }
}

void applyWholeSeq(Cube &C, const vector<Move>& seq){
    for(auto mv: seq){
        C.rotate_whole_cube(mv.first, mv.second);
    }
}

void applySliceInstruction(Cube &C, int faceSide, int k, const string& dir){
    const vector<Move>& seqTo = orientSeqToFront[faceSide];
    const vector<Move>& seqBack = orientSeqFromFront[faceSide];

    applyWholeSeq(C, seqTo);

    string d = dir;
    for(auto &ch : d) if(ch>='A' && ch<='Z') ch = char(ch - 'A' + 'a');
    if(d=="left" || d=="right"){
        int layer = k-1;
        int sgn = (d=="left"? +1 : -1);
        C.rotate_layer('Y', layer, sgn);
    } else if(d=="up" || d=="down"){
        int layer = k-1;
        int sgn = (d=="up"? +1 : -1);
        C.rotate_layer('X', layer, sgn);
    } else {
        int layer = k-1;
        int sgn = +1;
        C.rotate_layer('Y', layer, sgn);
    }

    applyWholeSeq(C, seqBack);
}

void applyGlobalOp(Cube &C, const string& line){
    string s = line;
    for(auto &ch:s) if(ch>='A' && ch<='Z') ch = char(ch - 'A' + 'a');
    if(s.find("turn")!=string::npos && s.find("left")!=string::npos){
        C.rotate_whole_cube('Y', +1);
    } else if(s.find("turn")!=string::npos && s.find("right")!=string::npos){
        C.rotate_whole_cube('Y', -1);
    } else if(s.find("rotate front")!=string::npos){
        C.rotate_whole_cube('X', +1);
    } else if(s.find("rotate back")!=string::npos){
        C.rotate_whole_cube('X', -1);
    } else if(s.find("rotate left")!=string::npos){
        C.rotate_whole_cube('Z', -1);
    } else if(s.find("rotate right")!=string::npos){
        C.rotate_whole_cube('Z', +1);
    } else {
        if(s.find("left")!=string::npos) C.rotate_whole_cube('Y', +1);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if(!(cin >> N >> K)) return 0;
    string tmp;
    getline(cin, tmp);

    vector<vector<string>> faces(6, vector<string>(N, string(N,' ')));
    for(int f=0; f<6; ++f){
        for(int i=0;i<N;++i){
            string line;
            getline(cin, line);
            while(line.size()==0){
                if(!getline(cin, line)) break;
            }
            vector<string> tokens;
            stringstream ss(line);
            string w;
            while(ss>>w) tokens.push_back(w);
            if((int)tokens.size() == N){
                for(int j=0;j<N;++j) faces[f][i][j] = tokens[j][0];
            } else {
                string compact;
                for(char c: line) if(!isspace((unsigned char)c)) compact.push_back(c);
                if((int)compact.size() == N){
                    for(int j=0;j<N;++j) faces[f][i][j] = compact[j];
                } else {
                    int idx=0;
                    for(auto &t: tokens){
                        if(idx<N) faces[f][i][idx++] = t[0];
                    }
                    while(idx<N) faces[f][i][idx++]='.';
                }
            }
        }
    }

    vector<Instr> instrs;
    instrs.reserve(K);
    for(int i=0;i<K;++i){
        string line;
        getline(cin, line);
        while(line.size()==0 && !cin.eof()){
            if(!getline(cin,line)) break;
        }
        Instr ins = parseInstrLine(line);
        ins.raw = line;
        instrs.push_back(ins);
    }

    precomputeOrientations();

    Cube initial = buildCubeFromFaces(faces);

    auto applyOne = [&](Cube &C, const Instr &ins){
        string low = ins.raw;
        string tmp = low;
        for(auto &ch: tmp) if(ch>='A'&& ch<='Z') ch = char(ch - 'A' + 'a');
        if(ins.isGlobal){
            applyGlobalOp(C, ins.raw);
        } else {
            int face = sideNameToFace(ins.side);
            if(face==-1){
                stringstream ss(tmp);
                vector<string> t;
                string w;
                while(ss>>w) t.push_back(w);
                if(t.size()>=3){
                    face = sideNameToFace(t[0]);
                    int kk = stoi(t[1]);
                    string dr = t[2];
                    applySliceInstruction(C, face, kk, dr);
                }
            } else {
                applySliceInstruction(C, face, ins.k, ins.dir);
            }
        }
    };

    for(int skip=0; skip<K; ++skip){
        Cube C = initial.copy();
        for(int i=0;i<K;++i){
            if(i==skip) continue;
            applyOne(C, instrs[i]);
        }
        if(C.anyFaceSolved()){
            cout << instrs[skip].raw << "\n";
            return 0;
        }
    }

    for(int f=0; f<6; ++f){
        for(int i=0;i<N;++i) for(int j=0;j<N;++j){
            char orig = faces[f][i][j];
            for(char cand='A'; cand<='Z'; ++cand){
                if(cand==orig) continue;
                vector<vector<string>> faces2 = faces;
                faces2[f][i][j] = cand;
                Cube C2 = buildCubeFromFaces(faces2);
                for(int skip=0; skip<K; ++skip){
                    Cube C = C2.copy();
                    for(int t=0;t<K;++t){
                        if(t==skip) continue;
                        applyOne(C, instrs[t]);
                    }
                    if(C.anyFaceSolved()){
                        cout << "Faulty\n";
                        cout << instrs[skip].raw << "\n";
                        return 0;
                    }
                }
            }
        }
    }

    cout << "Not Possible\n";
    return 0;
}


struct edge
{
    int u,v;
    int other(int i)
    {
        return i^u^v;
    }
};
edge es[mxN];
void dfs(int i, int p=0, int d=0, int pedg=-1)
{
    up[0][i]=p, down[i]=d, in[i] = timer_++;
    if(p) pe[i]=pedg;
    for(int j = 1; j < mxlogN; j++) up[j][i]=up[j-1][up[j-1][i]];
    for(int e : adj[i]) if(es[e].other(i)!=p) dfs(es[e].other(i), i, d+1, e);
    out[i] = timer_;
}

vector<int> adj[mxN], ord;
int up[mxlogN][mxN],down[mxN],in[mxN],out[mxN],who[mxN],f[mxN],timer_;
void dfs(int i=1, int p=1, int d=0)
{
    up[0][i]=p, down[i]=d, who[in[i]=timer_++]=i, f[i]=ord.size();
    ord.push_back(i);
    for(int j=1; j<mxlogN; j++) up[j][i]=up[j-1][up[j-1][i]];
    for(int j:adj[i]) if(j^p) dfs(j,i,d+1), ord.push_back(i);;
    out[i]=timer_;
}
int goup(int i, int k)
{
    for(int j=0; j<mxlogN; j++) if(k&1<<j) i=up[j][i];
    return i;
}
int lca(int i, int j)
{
    if(down[i]<down[j]) swap(i,j);
    i=goup(i,down[i]-down[j]);
    if(i==j) return i;
    for(int k=mxlogN-1; k>=0; k--) if(up[k][i]^up[k][j]) i=up[k][i], j=up[k][j];
    return up[0][i];
}
int dist(int i, int j)
{
    return down[i]+down[j]-2*down[lca(i,j)];
}


vector<int> bfs(int s, vector<vector<int>> &adj)
{
    int n=adj.size()-1;
    vector<int> dis(n+1,-1);
    queue<int> q; q.push(s);
    dis[s]=0;
    while(q.size())
    {
        int i=q.front(); q.pop();
        for(int j:adj[i]) if(!~dis[j])
        {
            dis[j]=dis[i]+1;
            q.push(j);
        }
    }
    return dis;
}
vector<int> dist(vector<vector<int>> &adj)
{
    auto dis=bfs(1,adj);
    int s=max_element(dis.begin()+1,dis.end())-dis.begin();
    dis=bfs(s,adj);
    int t=max_element(dis.begin()+1,dis.end())-dis.begin();
    auto tmp=bfs(t,adj);
    for(int i=1; i<adj.size(); i++) dis[i]=max(dis[i],tmp[i]);
    return dis;
}

///------------------ sparse table
//pazi na mxlogN (2n)

    build(2*n-1);

pair<int,int> sp[mxlogN][mxN];
void build(int n)
{
    for(int i=0; i<n; i++) sp[0][i]={down[ord[i]],ord[i]};
    for(int j=1; j<mxlogN; j++)
        for(int i=0; i+(1<<(j-1))<n; i++)
            sp[j][i]=min(sp[j-1][i],sp[j-1][i+(1<<(j-1))]);
}
int log2_floor(ull i)
{
    return i?__builtin_clzll(1)-__builtin_clzll(i):-1;
}
int lca(int u, int v) //[l,r]
{
    int l=min(f[u],f[v]), r=max(f[u],f[v]);
    int lg=log2_floor(r-l+1);
    return min(sp[lg][l],sp[lg][r-(1<<lg)+1]).second;
}

///------------------ seg tree
int sz, mx[mxN], mx2[mxN], tag[mxN];
void recalc(int i)
{
    mx[i]=max(mx[i<<1],mx[i<<1|1]);
    if(mx[i]==mx[i<<1]) mx2[i]=mx2[i<<1];
    else mx2[i]=mx2[i<<1|1];
}
void build2(int n, int i=1, int lx=0, int rx=sz)
{
    if(rx-lx==1)
    {
        if(lx<n) mx[i]=down[who[lx]], mx2[i]=who[lx];
        return;
    }
    int m=lx+rx>>1;
    build2(n,i<<1,lx,m);
    build2(n,i<<1|1,m,rx);
    recalc(i);
}
void build(int n)
{
    sz=1;
    while(sz<n) sz<<=1;
    for(int i=1; i<2*sz; i++) tag[i]=mx[i]=mx2[i]=0;
    build2(n);
}
void lazy(int i)
{
    if(tag[i])
    {
        mx[i<<1]+=tag[i];
        tag[i<<1]+=tag[i];
        mx[i<<1|1]+=tag[i];
        tag[i<<1|1]+=tag[i];
        tag[i]=0;
    }
}
void upd(int l, int r, ll v, int i=1, int lx=0, int rx=sz)
{
    if(lx>=r || rx<=l) return;
    if(lx>=l && rx<=r)
    {
        mx[i]+=v;
        tag[i]+=v;
        return;
    }
    int m=lx+rx>>1;
    lazy(i);
    upd(l,r,v,i<<1,lx,m);
    upd(l,r,v,i<<1|1,m,rx);
    recalc(i);
}
pair<int,int> qry(int l, int r, int i=1, int lx=0, int rx=sz)
{
    if(lx>=r || rx<=l) return {0,0};
    if(lx>=l && rx<=r) return {mx[i],mx2[i]};
    lazy(i);
    int m=lx+rx>>1;
    auto L=qry(l,r,i<<1,lx,m), R=qry(l,r,i<<1|1,m,rx);
    if(L<R) return R;
    else return L;
}
void upd(int pos, int v, int i=1, int lx=0, int rx=sz)
{
    if(rx-lx==1)
    {
        mn[i]=v;
        return;
    }
    lazy(i);
    int m=lx+rx>>1;
    if(pos<m) upd(pos,v,i<<1,lx,m);
    else upd(pos,v,i<<1|1,m,rx);
    recalc(i);
}
ll qry(int pos, int i=1, int lx=0, int rx=sz)
{
    if(rx-lx==1) return 0;
    lazy(i);
    int m=lx+rx>>1;
    if(pos<m) return qry(pos,i<<1,lx,m);
    else return qry(pos,i<<1|1,m,rx);
}

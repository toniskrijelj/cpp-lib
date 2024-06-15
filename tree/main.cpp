
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

vector<int> adj[mxN];
int up[mxlogN][mxN],down[mxN],in[mxN],out[mxN],who[mxN],timer_;
void dfs(int i=1, int p=1, int d=0)
{
    up[0][i]=p, down[i]=d, who[in[i]=timer_++]=i;
    for(int j=1; j<mxlogN; j++) up[j][i]=up[j-1][up[j-1][i]];
    for(int j:adj[i]) if(j^p) dfs(j,i,d+1);
    out[i]=timer_;
}
int goup(int i, int k)
{
    for(int j=mxlogN-1; j>=0; j--) if(k&1<<j) i=up[j][i];
    return i;
}
int lca(int i, int j)
{
    if(down[i]<down[j]) swap(i,j);
    i=goup(i, down[i]-down[j]);
    if(i==j) return i;
    for(int k=mxlogN-1; k>=0; k--) if(up[k][i]!=up[k][j]) i=up[k][i], j=up[k][j];
    return up[0][i];
}
int dist(int i, int j)
{
    return down[i]+down[j]-2*down[lca(i,j)];
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

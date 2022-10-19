
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
int up[mxlogN][mxN], down[mxN], in[mxN], out[mxN], timer_;
int a[mxN];

void dfs(int i=1, int p=1, int d=0)
{
    up[0][i]=p, down[i]=d, in[i]=timer_++;
    for(int j=1; j<mxlogN; j++) up[j][i]=up[j-1][up[j-1][i]];
    for(int j:adj[i]) if(j!=p) dfs(j,i,d+1);
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
int sz;
void build(int n)
{
    sz=1;
    while(sz<n) sz<<=1;
}
ll sum[mxN];
void add(int l, int r, ll v, int i=0, int Lx=0, int Rx=sz)
{
    if(Rx<=l || Lx>=r) return;
    if(Lx>=l && Rx<=r)
    {
        sum[i]+=v;
        return;
    }
    int m=(Rx+Lx)/2;
    add(l,r,v,i*2+1,Lx,m);
    add(l,r,v,i*2+2,m,Rx);
}
ll get(int pos, int i=0, int Lx=0, int Rx=sz)
{
    if(Rx-Lx==1) return sum[i];
    int m=(Rx+Lx)/2;
    if(pos<m) return sum[i]+get(pos,i*2+1,Lx,m);
    else return sum[i]+get(pos,i*2+2,m,Rx);
}

int root[mxN];
bool vis[mxN];
vector<int> out[mxN],in[mxN],order;
struct edge
{
    int u,v; ll w;
    int other(int i)
    {
        return i^u^v;
    }
}es[mxN];
void dfs(int i)
{
    if(vis[i]) return;
    vis[i]=1;
    for(int e:out[i]) dfs(es[e].v);
    order.push_back(i);
}
vector<int> who[mxN];
void assign(int i, int r)
{
    if(~root[i]) return;
    root[i]=r;
    who[r].push_back(i);
    for(int e:in[i]) assign(es[e].u,r);
}
vector<int> inc[mxN],outc[mxN];
int setup(int n, int m)
{
    for(int i=0; i<n; i++) vis[i]=0,root[i]=-1;
    for(int i=0; i<n; i++) dfs(i);
    reverse(order.begin(), order.end());
    int comps=0;
    for(int i:order)
    {
        if(~root[i]) continue;
        assign(i, comps++);
    }
    for(int e=0; e<m; e++)
    {
        es[e].u=root[es[e].u],es[e].v=root[es[e].v];
        if(es[e].u!=es[e].v) outc[es[e].u].push_back(e);
    }
    return comps;
}

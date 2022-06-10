struct edge
{
    int u,v,w;
    int other(int i)
    {
        return u^v^i;
    }
};
edge es[mxN];
bool vis[mxN];
int cc[mxN];
vector<int> adj[mxN];
void init(int i, int p=-1)
{
    cc[i]=1;
    for(int e:adj[i])
    {
        int j=es[e].other(i);
        if(p==j||vis[j]) continue;
        init(j,i);
        cc[i]+=cc[j];
    }
}
int find_centroid(int i, int n, int p=-1)
{
    for(int e:adj[i])
    {
        int j=es[e].other(i);
        if(p==j||vis[j]) continue;
        if(cc[j]>n/2) return find_centroid(j,n,i);
    }
    return i;
}
int solve(int i)
{
    init(i);
    i=find_centroid(i,cc[i]);
    vis[i]=1;
    for(int e:adj[i])
    {
        int j=es[e].other(i);
        if(vis[j]) continue;
        solve2(j);
    }
    for(int e:adj[i])
    {
        int j=es[e].other(i);
        if(vis[j]) continue;
        solve(j);
    }
}

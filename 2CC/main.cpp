struct edge
{
    int u, v; bool cut=0;
    int other(int i)
    {
        return i^u^v;
    }
};
edge es[mxN];
int vis[mxN],lowlink[mxN],_time[mxN],_timer;
vector<int> adj[mxN];
void dfs(int i, int p=-1) ///parent edge
{
    lowlink[i]=_time[i]=_timer++;
    vis[i]=1;
    for(int e:adj[i])
    {
        int j=es[e].other(i);
        if(e==p||vis[j]==2) continue;
        if(vis[j]) lowlink[i]=min(lowlink[i],_time[j]);
        else
        {
            dfs(j,e);
            lowlink[i]=min(lowlink[i],lowlink[j]);
            if(lowlink[j]>_time[i]) es[e].cut=1;
        }
    }
    vis[i]=2;
}
int sz=0;
int root[mxN];
vector<int> who[mxN];
void dfs2(int i, int r)
{
    vis[i]=1;
    root[i]=r;
    who[r].push_back(i);
    for(int e:adj[i])
    {
        int j=es[e].other(i);
        if(es[e].cut||vis[j]) continue;
        dfs2(j,r);
    }
}
vector<int> adjc[mxN];
void setup(int n, int m)
{
    for(int i=0; i<n; i++) vis[i]=0;
    for(int i=0; i<n; i++) if(!vis[i]) dfs(i);
    for(int i=0; i<n; i++) vis[i]=0;
    for(int i=0; i<n; i++) if(!vis[i]) dfs2(i,sz++);
    for(int i=0; i<m; i++)
    {
        if(es[i].cut)
        {
            int u=root[es[i].u], v=root[es[i].v]; ///edges were changed
            es[i].u=u, es[i].v=v;
            adjc[u].push_back(i);
            adjc[v].push_back(i);
        }
    }
    //for(int i=0; i<sz; i++) vis[i]=0;
    //for(int i=0; i<sz; i++) if(!vis[i]) dfs3(i);
}
void clear_all()
{
    ///clear
}

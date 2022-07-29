struct edge
{
    int u, v, root;
    int other(int i)
    {
        return i^u^v;
    }
};
edge es[mxN];
int vis[mxN],lowlink[mxN],_time[mxN],_timer;
bool cut[mxN];
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
            if(lowlink[j]>_time[i]) cut[e]=1;
        }
    }
    vis[i]=2;
}

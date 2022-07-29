int vis[mxN],lowlink[mxN],_time[mxN],_timer;
vector<int> adj[mxN];
bool cut[mxN];
void dfs(int i, int p=-1)
{
    lowlink[i]=_time[i]=_timer++;
    vis[i]=1;
    int cnt=0;
    for(int e:adj[i])
    {
        int j=es[e].other(i);
        if(e==p||vis[j]==2) continue;
        if(vis[j]) lowlink[i]=min(lowlink[i],_time[j]);
        else
        {
            cnt++;
            dfs(j,e);
            lowlink[i]=min(lowlink[i],lowlink[j]);
            if(lowlink[j]>=_time[i]) cut[i]=1;
        }
    }
    vis[i]=2;
    if(!~p) cut[i]=cnt>1;
}

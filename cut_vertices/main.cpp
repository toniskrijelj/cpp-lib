int vis[mxN];
int lowlink[mxN];
int _time[mxN];
int _timer;
vector<int> adj[mxN];
bool cut[mxN];
void dfs(int i, int p=0)
{
    lowlink[i]=_time[i]=_timer++;
    vis[i]=1;
    int cnt=0;
    for(int j:adj[i])
    {
        if(j==p||vis[j]==2) continue;
        if(vis[j]) lowlink[i]=min(lowlink[i],_time[j]);
        else
        {
            cnt++;
            dfs(j, i);
            lowlink[i]=min(lowlink[i],lowlink[j]);
            if(lowlink[j] >= _time[i]) cut[i] = 1;
        }
    }
    vis[i]=2;
    if(i==1) cut[i]=cnt>1;
}

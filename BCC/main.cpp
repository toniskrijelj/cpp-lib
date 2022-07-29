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
stack<int> s;
int sz=0;
vector<int> whoE[mxN], whoV[mxN];
int root[mxN];
void extract(int e)
{
    int r=sz++;
    while(1)
    {
        int e2=s.top();
        s.pop();
        es[e2].root=r;
        whoE[r].push_back(e2);
        whoV[r].push_back(es[e2].u);
        whoV[r].push_back(es[e2].v);
        if(e==e2) break;
    }
    sort(whoV[r].begin(), whoV[r].end());
    whoV[r].erase(unique(whoV[r].begin(),whoV[r].end()),whoV[r].end());
}
void dfs(int i, int p=-1) ///parent edge
{
    lowlink[i]=_time[i]=_timer++;
    vis[i]=1;
    int cnt=0;
    for(int e:adj[i])
    {
        int j=es[e].other(i);
        if(e==p||vis[j]==2) continue;
        s.push(e);
        if(vis[j]) lowlink[i]=min(lowlink[i],_time[j]);
        else
        {
            cnt++;
            dfs(j,e);
            lowlink[i]=min(lowlink[i],lowlink[j]);
            if(lowlink[j]>=_time[i])
            {
                cut[i]=1;
                extract(e);
            }
        }
    }
    vis[i]=2;
    if(!~p) cut[i]=cnt>1;
}
vector<int> adjc[mxN];
void setup(int n)
{
    for(int i=0; i<n; i++) if(!vis[i]) dfs(i);
    for(int i=0; i<n; i++) if(cut[i])
    {
        root[i]=sz++;
        whoV[root[i]]={i};
    }
    for(int r=0; r<sz; r++)
    {
        for(int e:whoE[r])
        {
            int i=es[e].u, j=es[e].v;
            if(cut[i]) adjc[root[i]].push_back(r);
            if(cut[j]) adjc[root[j]].push_back(r);
        }
    }
    for(int i=0; i<n; i++) if(cut[i]) for(int e:adj[i]) adjc[es[e].root].push_back(root[i]);
    for(int i=0; i<sz; i++) adjc[i].erase(unique(adjc[i].begin(), adjc[i].end()), adjc[i].end());
}
void clear_all(int n)
{
    for(int i=0; i<max(n,sz); i++)
    {
        adjc[i].clear();
        whoE[i].clear();
        whoV[i].clear();
        adj[i].clear();
        cut[i]=0;
        vis[i]=0;
    }
    _timer=0;
    sz=0;
}

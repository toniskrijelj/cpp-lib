struct edge
{
    int u,v;
    int other(int i)
    {
        return i^u^v;
    }
};
edge es[mxN];
vector<int> adj[mxN];
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++)
    {
        int u, v, c; cin >> u >> v >> c;
        es[i]={u,v,c};
        adj[u].push_back(i);
        adj[v].push_back(i);
    }
}

int _t;
int order[mxN];
void dfs2(int i) ///topo sort
{
    if(order[i]) return;
    for(int e : adj[i])
    {
        int j = es[e].u;
        dfs2(j);
    }
    order[i]=++_t;
}

int vis[mxN];
vector<int> adj[mxN];
bool dfs(int i) ///cycle detection
{
    vis[i]=1;
    for(int e : adj[i])
    {
        int j = es[e].v;
        if(vis[j]==1) return 1;
        if(!vis[j]) if(dfs(j)) return 1;
    }
    vis[i]=2;
    return 0;
}

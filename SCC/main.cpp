int root[mxN];
bool vis[mxN];
vector<int> out[mxN],in[mxN],order;
void dfs(int i)
{
    if(vis[i]) return;
    vis[i]=1;
    for(int j:out[i]) dfs(j);
    order.push_back(i);
}
vector<int> who[mxN];
void assign(int i, int r)
{
    if(~root[i]) return;
    root[i]=r;
    who[r].push_back(i);
    for(int j:in[i]) assign(j, r);
}
vector<int> inc[mxN],outc[mxN];
int setup(int n)
{
    for(int i=0; i<n; i++) vis[i]=0,root[i]=-1;
    for(int i=0; i<n; i++) dfs(i);
    reverse(order.begin(), order.end());
    int comps=0;
    for(int i:order)
    {
        if(~root[i]) continue;
        assign(i,comps++);
    }
    for(int c=0; c<comps; c++)
    {
        for(int i:who[c])
        {
            for(int j:out[i])
            {
                if(root[i]!=root[j])
                {
                    inc[root[j]].push_back(root[i]);
                }
            }
            for(int j:in[i])
            {
                if(root[i]!=root[j])
                {
                    outc[root[j]].push_back(root[i]);
                }
            }
        }
    }
    for(int i=0; i<comps; i++)
    {
        outc[i].erase(unique(outc[i].begin(), outc[i].end()), outc[i].end());
        inc[i].erase(unique(inc[i].begin(), inc[i].end()), inc[i].end());
    }
    return comps;
}

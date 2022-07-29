vector<int> out[mxN],in[mxN];
int ord[mxN],when[mxN],_time,sdom[mxN],idom[mxN],p[mxN],ans[mxN];
vector<int> who[mxN],child[mxN];
bool fix[mxN];
void dfs(int i)
{
    _time++;
    ord[_time]=ans[i]=p[i]=i;
    idom[i]=sdom[i]=_time;
    for(int j:out[i])
    {
        in[j].push_back(i);
        if(idom[j]) continue;
        child[i].push_back(j);
        dfs(j);
    }
}
int query(int x)
{
    if(p[x]==x) return ans[x];
    int y=query(p[x]);
    if(sdom[ans[x]]>sdom[y]) ans[x]=y;
    p[x]=p[p[x]];
    return ans[x];
}
void setup(int n, int s)
{
    dfs(s);
    for(int t=_time; t; t--)
    {
        int i=ord[t];
        for(int j:in[i]) sdom[i]=min(sdom[i],sdom[query(j)]);
        who[ord[sdom[i]]].push_back(i);
        for(int j:who[i])
        {
            int k=query(j);
            if(sdom[j]==sdom[k]) idom[j]=ord[sdom[j]];
            else
            {
                idom[j]=k;
                fix[j]=1;
            }
        }
        for(int j:child[i]) p[j]=i;
        child[i].clear();
    }
    for(int t=1; t<=_time; t++)
    {
        int i=ord[t];
        if(fix[i]) idom[i]=idom[idom[i]];
        if(idom[i]!=i) child[idom[i]].push_back(i);
    }
}

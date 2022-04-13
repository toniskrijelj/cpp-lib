vector<int> who[mxN];
int comp[mxN];
bool pty[mxN];
void unite(int u, int v)
{
    bool b=pty[u]==pty[v];
    u=comp[u],v=comp[v];
    if(who[u].size()>who[v].size()) swap(u,v);
    while(who[u].size())
    {
        int x=who[u].back();
        who[u].pop_back();
        pty[x]^=b;
        comp[x]=v;
        who[v].push_back(x);
    }
}
void clear(int i)
{
    who[i].clear();
    who[i].push_back(i);
    comp[i]=i;
    pty[i]=0;
}
void init(int n)
{
    for(int i = 0; i < n; i++) clear(i);
}

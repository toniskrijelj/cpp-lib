
int root[mxN];
bool vis[mxN];
vector<int> out[mxN],in[mxN],order;
void dfs(int i)
{
    if(vis[i]) return;
    vis[i]=1;
    for(int j : out[i]) dfs(j);
    order.push_back(i);
}
void assign(int i, int r)
{
    if(~root[i]) return;
    root[i]=r;
    for(int j : in[i]) assign(j, r);
}
void setup(int n)
{
    for(int i=0; i<n; i++) root[i]=-1, vis[i]=0;
    for(int i=0; i<n; i++) dfs(i);
    reverse(order.begin(), order.end());
    int comps=0;
    for(int i:order)
    {
        if(~root[i]) continue;
        assign(i, comps++);
    }
}
void add_edge(int x, int y)
{
    out[x].push_back(y);
    in[y].push_back(x);
}
void either(int x, int y)
{
    add_edge(x^1,y);
    add_edge(y^1,x);
}
void must(int x)
{
    either(x,x);
}
void implies(int x, int y)
{
    either(x^1,y);
}
void equals(int x, int y)
{
    implies(x,y);
    implies(y,x);
}
///root[i]>root[i^1] => + else -

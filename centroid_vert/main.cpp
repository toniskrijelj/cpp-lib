int vis[mxN], cc[mxN];
vector<int> adj[mxN];
int init(int i, int p=0)
{
    cc[i]=1;
    for(int j:adj[i])
    if(!vis[j]&&p^j)
    init(j,i), cc[i]+=cc[j];
}
int find_centroid(int i, int n, int p=0)
{
    for(int j:adj[i])
    if(!vis[j]&&p^j&&cc[j]>n/2)
    return find_centroid(j,n,i);
    return i;
}
void solve(int i)
{
    init(i);
    i=find_centroid(i,cc[i]);
    vis[i]=1;

    for(int j:adj[i])
    if(!vis[j])
    solve2(j);

    for(int j:adj[i])
    if(!vis[j])
    solve(j);
}

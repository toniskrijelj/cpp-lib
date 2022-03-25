
const int SIZE = 2;
const int mxlogN = 20;
vector<int> adj[SIZE][mxN];
int up[SIZE][mxlogN][mxN], down[SIZE][mxN], timer_[SIZE], in[SIZE][mxN], out[SIZE][mxN];
void dfs(int i, int b, int p=1, int d=0)
{
    up[b][0][i]=p, down[b][i]=d, in[b][i]=timer_[b]++;
    for(int j = 1; j < mxlogN; j++) up[b][j][i]=up[b][j-1][up[b][j-1][i]];
    for(int j : adj[b][i]) if(j!=p) dfs(j, b, i, d+1);
    out[b][i]=timer_[b];
}
int root[mxN], R;
void dfs2(int i, int p=1, int b=0)
{
    int preR = R;
    root[i] = R = update(in[!b][i], out[!b][i], +1, R);
    for(int j : adj[b][i]) if(j!=p) dfs2(j, i, b);
    R = preR;
}
int goup(int i, int k, int b)
{
    if(!k) return i;
    for(int j = mxlogN-1; j>=0; j--)
    {
        if(k>(1<<j))
        {
            k-=1<<j;
            i = up[b][j][i];
        }
    }
    return up[b][0][i];
}
int lca(int i, int j, int b)
{
    if(down[b][i] < down[b][j]) swap(i,j);
    i = goup(i, down[b][i]-down[b][j], b);
    if(i==j) return i;
    for(int k = mxlogN-1; k>=0; k--)
    {
        if(up[b][k][i]!=up[b][k][j])
        {
            i = up[b][k][i], j = up[b][k][j];
        }
    }
    return up[b][0][i];
}

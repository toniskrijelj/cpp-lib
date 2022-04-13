int sz[mxN];
int nex[mxN][mxK];
void merge(int a, int b) ///merges b to a
{
    if(!b) return;
    sz[a]=1;
    for(int j = 0; j < mxK; j++)
    {
        if(!nex[a][j]) nex[a][j]=nex[b][j];
        else
        {
            if(sz[nex[a][j]] < sz[nex[b][j]]) swap(nex[a][j], nex[b][j]);
            merge(nex[a][j], nex[b][j]);
        }
        sz[a]+=sz[nex[a][j]];
    }
}

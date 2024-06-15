ll sp[mxlogN][mxN];
void build(int n)
{
    for(int i=0; i<n; i++) sp[0][i]=a[i];
    for(int j=1; j<mxlogN; j++)
        for(int i=0; i+(1<<(j-1))<n; i++)
            sp[j][i]=op(sp[j-1][i],sp[j-1][i+(1<<(j-1))]);
}
int log2_floor(ull i)
{
    return i?__builtin_clzll(1)-__builtin_clzll(i):-1;
}
int qrymn(int l, int r) //[l,r]
{
    int lg=log2_floor(r-l+1);
    return op(sp[lg][l],sp[lg][r-(1<<lg)+1]);
}

ll st[mxlogN][mxN][mxlogN][mxN];
void build(int n)
{
    for(int j=0; j<n; j++)
    {
        for(int i=0; i<n; i++) st[0][j][0][i]=v[j][i];
        for(int k=1; k<mxlogN; k++)
            for(int i=1; i+(1<<(k-1))<n; i++)
                st[0][j][k][i]=max(st[0][j][k-1][i],st[0][j][k-1][i+(1<<(k-1))]);
    }
    for(int k=1; k<mxlogN; k++)
        for(int j=1; j+(1<<(k-1))<n; j++)
            for(int k2=0; k2<mxlogN; k2++)
                for(int i=1; i<n; i++)
                    st[k][j][k2][i]=max(st[k-1][j][k2][i],st[k-1][j+(1<<(k-1))][k2][i]);
}
int log2_floor(ull i)
{
    return i?__builtin_clzll(1)-__builtin_clzll(i):-1;
}
ll qry(int y2, int x2, int y, int x) //[x2,x][y2,y];
{
    if(y2>y||x2>x) return -inf;
    int k=log2_floor(y-y2+1);
    int k2=log2_floor(x-x2+1);
    ll r1=max(st[k][y2][k2][x2],st[k][y2][k2][x-(1<<k2)+1]);
    ll r2=max(st[k][y-(1<<k)+1][k2][x2],st[k][y-(1<<k)+1][k2][x-(1<<k2)+1]);
    return max(r1,r2);
}

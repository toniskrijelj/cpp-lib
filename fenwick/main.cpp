ll fw[mxN];
ll get(int x) ///sum first x elemens
{
    ll res = 0;
    while(x)
    {
        res+=fw[x];
        x-=x&-x;
    }
    return res;
}
void add(int x, ll v)
{
    while(x<mxN)
    {
        fw[x]+=v;
        x+=x&-x;
    }
}

ll fw[mxN][mxN];
ll sum(int y, int x)
{
    ll s=0;
    while(y)
    {
        int xx=x;
        while(x)
        {
            s+=ft[y][x];
            x-=x&-x;
        }
        x=xx;
        y-=y&-y;
    }
    return s;
}
void add(int y, int x, int v)
{
    while(y<mxN)
    {
        int xx=x;
        while(x<mxN)
        {
            ft[y][x]+=v;
            x+=x&-x;
        }
        x=xx;
        y+=y&-y;
    }
}

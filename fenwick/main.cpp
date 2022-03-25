ll fw[mxN];
ll get(int x) ///sum first x elemens
{
    ll res = 0;
    while(x)
    {
        res += fw[x];
        x -= x&-x;
    }
    return res;
}
void add(int x, ll v)
{
    while(x < mxN)
    {
        fw[x] += v;
        x += x&-x;
    }
}

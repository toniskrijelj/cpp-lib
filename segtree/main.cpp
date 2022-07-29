int sz;
int mx[mxN];
void recalc(int i, int Lx=0, int Rx=0)
{

}
void build2(int n, int i=0, int Lx=0, int Rx=sz)
{
    if(Rx-Lx==1)
    {
        if(Lx<n)
        {

        }
        return;
    }
    int m = (Lx+Rx)/2;
    build2(n, i*2+1, Lx, m);
    build2(n, i*2+2, m, Rx);
    recalc(i, Lx, Rx);
}
void build(int n)
{
    sz = 1;
    while(sz < n) sz <<= 1;
    build2(n);
}
void lazy(int i, int Lx=0, int Rx=0)
{

}
void add(int l, int r, ll v, int i=0, int Lx=0, int Rx=sz)
{
    if(Rx <= l || Lx >= r) return;
    if(Lx >= l && Rx <= r)
    {

        return;
    }
    int m = (Rx+Lx)/2;
    lazy(i, Lx, Rx);
    add(l, r, v, i*2+1, Lx, m);
    add(l, r, v, i*2+2, m, Rx);
    recalc(i, Lx, Rx);
}
void SET(int pos, int v, int i=0, int Lx=0, int Rx=sz)
{
    if(Rx-Lx==1)
    {
        mn[i]=v;
        return;
    }
    lazy(i, Lx, Rx);
    int m = (Rx+Lx)/2;
    if(pos<m) SET(pos,v,i*2+1,Lx,m);
    else SET(pos,v,i*2+2,m,Rx);
    recalc(i, Lx, Rx);
}
ll qry(int l, int r, int i=0, int Lx=0, int Rx=sz)
{
    if(Rx <= l || Lx >= r) return 1e9;
    if(Lx >= l && Rx <= r) return 0;
    lazy(i, Lx, Rx);
    int m = (Rx+Lx)/2;
    return qry(l,r,i*2+1,Lx,m), qry(l,r,i*2+2,m,Rx);
}
ll qry(int pos, int i=0, int Lx=0, int Rx=sz)
{
    if(Rx-Lx==1) return ;
    lazy(i, Lx, Rx);
    int m = (Rx+Lx)/2;
    if(pos<m) return +qry(pos,i*2+1,Lx,m);
    else return +qry(pos,i*2+2,m,Rx);
}

int sz, mn[mxN], tag[mxN];
void recalc(int i)
{

}
void build2(int n, int i=1, int lx=0, int rx=sz)
{
    if(rx-lx==1)
    {
        if(lx<n) ;
        return;
    }
    int m=lx+rx>>1;
    build2(n,i<<1,lx,m);
    build2(n,i<<1|1,m,rx);
    recalc(i);
}
void build(int n)
{
    sz=1;
    while(sz<n) sz<<=1;
    build2(n);
}
void lazy(int i)
{
    if(tag[i])
    {
        mn[i<<1]+=tag[i];
        tag[i<<1]+=tag[i];
        mn[i<<1|1]+=tag[i];
        tag[i<<1|1]+=tag[i];
        tag[i]=0;
    }
}
void upd(int l, int r, ll v, int i=1, int lx=0, int rx=sz)
{
    if(lx>=r || rx<=l) return;
    if(lx>=l && rx<=r)
    {
        mn[i]+=v;
        tag[i]+=v;
        return;
    }
    int m=lx+rx>>1;
    lazy(i);
    upd(l,r,v,i<<1,lx,m);
    upd(l,r,v,i<<1|1,m,rx);
    recalc(i);
}
void upd(int pos, int v, int i=1, int lx=0, int rx=sz)
{
    if(rx-lx==1)
    {
        mn[i]=v;
        return;
    }
    lazy(i);
    int m=lx+rx>>1;
    if(pos<m) upd(pos,v,i<<1,lx,m);
    else upd(pos,v,i<<1|1,m,rx);
    recalc(i);
}
ll qry(int l, int r, int i=1, int lx=0, int rx=sz)
{
    if(lx>=r || rx<=l) return 0;
    if(lx>=l && rx<=r) return mn[i];
    lazy(i);
    int m=lx+rx>>1;
    return qry(l,r,i<<1,lx,m) + qry(l,r,i<<1|1,m,rx);
}
ll qry(int pos, int i=1, int lx=0, int rx=sz)
{
    if(rx-lx==1) return 0;
    lazy(i);
    int m=lx+rx>>1;
    if(pos<m) return qry(pos,i<<1,lx,m);
    else return qry(pos,i<<1|1,m,rx);
}
// https://atcoder.jp/contests/abc365/submissions/56462288 clamp segment tree
/*
struct block
{
    ll fL, fU, gL, gU, C;
    pair<ll,ll> operator()(ll y) const
    {
        return {clamp(y,fL,fU),C+max(y,gL)-min(y,gU)};
    }
};
block op(block a, block b)
{
    ll fL=clamp(a.fL,b.fL,b.fU), fU=clamp(a.fU,b.fL,b.fU);
    ll gL=clamp(b.gL,a.gL,a.gU), gU=clamp(b.gU,a.gL,a.gU);
    ll C=a.C+b(a(gU).first).second;
    return {fL,fU,gL,gU,C};
}
block e()
{
    return {0,inf,0,inf,0};
}*/
/*
https://codeforces.com/contest/1942/problem/F
https://codeforces.com/contest/1936/problem/D

ll qry(int p, int i=1, int lx=0, int rx=sz)
{
    if(rx-lx==1) return val[i];
    lazy(i,lx,rx);
    int m=lx+rx>>1;
    if(lx>=p)
    {
        if(val[i]==rx-lx) return rx-lx;
        if(val[i<<1]==(rx-lx)/2) return (rx-lx)/2+qry(p,i<<1|1,m,rx);
        return qry(p,i<<1,lx,m);
    }
    if(p<m)
    {
        int res=qry(p,i<<1,lx,m);
        if(res==m-p) return res+qry(p,i<<1|1,m,rx);
        return res;
    }
    return qry(p,i<<1|1,m,rx);
}

int findr(int p, int v, int& x, int i=1, int lx=0, int rx=sz)
{
    if(rx-lx==1)
    {
        x|=orv[i];
        if(x>=v) return rx;
        return sz+1;
    }
    int m=lx+rx>>1;
    if(lx>=p)
    {
        if((x|orv[i])<v)
        {
            x|=orv[i];
            return sz+1;
        }
        if((x|orv[i<<1])>=v) return findr(p,v,x,i<<1,lx,m);
        x|=orv[i<<1];
        return findr(p,v,x,i<<1|1,m,rx);
    }
    else
    {
        if(p<m)
        {
            int p2=findr(p,v,x,i<<1,lx,m);
            if(p2<=sz) return p2;
        }
        return findr(p,v,x,i<<1|1,m,rx);
    }
}
int findl(int p, int v, int& x, int i=1, int lx=0, int rx=sz)
{
    //cout << "x " << x << " " << lx << " " << rx << "\n";
    if(rx-lx==1)
    {
        x|=orv[i];
        if(x>=v) return lx;
        else return sz+1;
    }
    int m=lx+rx>>1;
    if(rx<=p)
    {
        if((x|orv[i])<v)
        {
            x|=orv[i];
            return sz+1;
        }
        if((x|orv[i<<1|1])>=v) return findl(p,v,x,i<<1|1,m,rx);
        x|=orv[i<<1|1];
        return findl(p,v,x,i<<1,lx,m);
    }
    else
    {
        if(p>m)
        {
            int p2=findl(p,v,x,i<<1|1,m,rx);
            if(p2<=sz) return p2;
        }
        return findl(p,v,x,i<<1,lx,m);
    }
}
*/

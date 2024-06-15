//https://codeforces.com/contest/1912/problem/G
struct st
{
    static const int sz=1<<19;
    ll val[sz<<1], mx[sz<<1], sum2[sz<<1], tag[sz<<1];
    void put(ll v, int i, int lx, int rx)
    {

    }
    void up(int i, int lx, int rx)
    {

    }
    void down(int i, int lx, int rx)
    {
        if(tag[i])
        {
            int m=lx+rx>>1;
            put(tag[i],i<<1,lx,m);
            put(tag[i],i<<1|1,m,rx);
            tag[i]=0;
        }
    }
    void build(int* a, int i=1, int lx=0, int rx=sz)
    {
        if(rx-lx==1)
        {
            put(a[lx],i,lx,rx);
            return;
        }
        int m=lx+rx>>1;
        build(a,i<<1,lx,m);
        build(a,i<<1|1,m,rx);
        up(i,lx,rx);
    }
    void upd(ll v, int l, int r, int i=1, int lx=0, int rx=sz)
    {
        if(l<=lx&&rx<=r)
        {
            put(v,i,lx,rx);
            return;
        }
        if(r<=lx||rx<=l) return;
        int m=lx+rx>>1;
        down(i,lx,rx);
        upd(v,l,r,i<<1,lx,m);
        upd(v,l,r,i<<1|1,m,rx);
        up(i,lx,rx);
    }
    ll eq(){return 0;}
    ll opq(ll l, ll r)
    {

    }
    ll qry(int l, int r, int i=1, int lx=0, int rx=sz)
    {
        if(l>=rx||lx>=r) return eq();
        if(l<=lx&&rx<=r) return sum[i];
        int m=lx+rx>>1;
        down(i,lx,rx);
        return opq(qry(v,l,r,i<<1,lx,m),qry(v,l,r,i<<1|1,m,rx));
    }
};

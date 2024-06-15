const int sz=1<<19;
///https://codeforces.com/contest/1912/problem/G
struct st
{
    ll sum[sz<<1], mx[sz<<1], sum2[sz<<1], tag[sz<<1];
    void put(ll v, int i, int lx, int rx)
    {
        tag[i]+=v;
        mx[i]+=v;
        sum[i]+=v*(rx-lx);
        int m=lx+rx>>1;
        sum2[i]+=v*(rx-m);
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
    ll calc(int i, ll v, int lx, int rx)
    {
        if(rx-lx==1) return max(v,mx[i]);
        down(i,lx,rx);
        int m=lx+rx>>1;
        if(v<=mx[i<<1]) return calc(i<<1,v,lx,m)+sum2[i];
        else return v*(m-lx)+calc(i<<1|1,v,m,rx);
    }
    void up(int i, int lx, int rx)
    {
        mx[i]=max(mx[i<<1],mx[i<<1|1]);
        int m=lx+rx>>1;
        sum2[i]=calc(i<<1|1,mx[i<<1],m,rx);
        sum[i]=sum[i<<1]+sum2[i];
    }
    void build(int* a, int i, int lx, int rx)
    {
        if(rx-lx==1)
        {
            mx[i]=sum[i]=a[lx];
            return;
        }
        int m=lx+rx>>1;
        build(a,i<<1,lx,m);
        build(a,i<<1|1,m,rx);
        up(i,lx,rx);
    }
    void upd(ll v, int l, int r, int i, int lx, int rx)
    {
        if(l<=lx&&rx<=r)
        {
            put(v,i,lx,rx);
            return;
        }
        if(r<=lx||rx<=l) return;
        down(i,lx,rx);
        int m=lx+rx>>1;
        upd(v,l,r,i<<1,lx,m);
        upd(v,l,r,i<<1|1,m,rx);
        up(i,lx,rx);
    }
}pf,sf;

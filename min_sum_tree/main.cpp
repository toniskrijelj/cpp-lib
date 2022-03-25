struct segTree
{
    struct node
    {
        ll mn;
        ll mx
    };
    int size;
    vector<node> val; /// minimum, sum count
    void build(int n, int i, int Lx, int Rx)
    {
        if(Rx-Lx==1)
        {
            if(Lx<n) val[i].mx = -rev[Lx];
            return;
        }
        int m = (Lx+Rx)/2;
        build(n, i*2+1, Lx, m);
        build(n, i*2+2, m, Rx);
        val[i].mx = max(val[i*2+1].mx, val[i*2+2].mx);
    }
    void build(int n)
    {
        size = 1;
        while(size < n) size <<= 1;
        val = vector<node>(size << 1, {0,0});
        ///build n i Lx Rx
    }
    void lazy(int i)
    {
        val[i*2+1].add += val[i].add;
        val[i*2+2].add += val[i].add;
        val[i*2+1].mn += val[i].add;
        val[i*2+2].mn += val[i].add;
        val[i].add = 0;
    }
    void add(int l, int r, ll v, int i, int Lx, int Rx)
    {
        if(Rx <= l || Lx >= r) return;
        if(Lx >= l && Rx <= r)
        {
            val[i].mn += v;
            val[i].add += v;
            return;
        }
        int m = (Rx+Lx)/2;
        lazy(i);
        add(l, r, v, i*2+1, Lx, m);
        add(l, r, v, i*2+2, m, Rx);
        val[i].mn = min(val[i*2+1].mn, val[i*2+2].mn);
    }
    void add(int l, int r, ll v)
    {
        add(l, r, v, 0, 0, size);
    }
    ll mn(int l, int r, int i, int Lx, int Rx)
    {
        if(Rx <= l || Lx >= r) return 1e9;
        if(Lx >= l && Rx <= r) return val[i].mn;
        lazy(i);
        int m = (Rx+Lx)/2;
        return min(mn(l,r,i*2+1,Lx,m), mn(l,r,i*2+2,m,Rx));
    }

    ll mn(int l, int r)
    {
        return mn(l, r, 0, 0, size);
    }
};

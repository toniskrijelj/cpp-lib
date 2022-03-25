///https://codeforces.com/contest/1609/submission/137863243

struct segTree
{
    struct node
    {
        int a,b,c,ab,bc,abc;
    };
    int size;
    vector<node> val; /// minimum, sum count
    node merge(node l, node r)
    {
        node nw;
        nw.a = l.a+r.a;
        nw.b = l.b+r.b;
        nw.c = l.c+r.c;
        nw.ab = min(l.ab+r.b, l.a+r.ab);
        nw.bc = min(l.bc+r.c, l.b+r.bc);
        nw.abc = min({l.a+r.abc, l.ab+r.bc, l.abc+r.c});
        return nw;
    }
    void build(int n, int i, int Lx, int Rx)
    {
        if(Rx-Lx==1)
        {
            if(Lx<n)
            {
                if(s[Lx]=='a') val[i].a=1;
                if(s[Lx]=='b') val[i].b=1;
                if(s[Lx]=='c') val[i].c=1;
            }
            return;
        }
        int m = (Lx+Rx)/2;
        build(n, i*2+1, Lx, m);
        build(n, i*2+2, m, Rx);
        val[i] = merge(val[i*2+1], val[i*2+2]);
    }
    void build(int n)
    {
        size = 1;
        while(size < n) size <<= 1;
        val = vector<node>(size << 1, {0,0,0,0,0,0});
        build(n, 0, 0, size);
    }
    void update(int pos, int i, int Lx, int Rx)
    {
        if(Rx-Lx==1)
        {
            val[i].a=val[i].b=val[i].c=0;
            if(s[Lx]=='a') val[i].a=1;
            if(s[Lx]=='b') val[i].b=1;
            if(s[Lx]=='c') val[i].c=1;
            return;
        }
        int m = (Rx+Lx)/2;
        if(pos < m) update(pos, i*2+1, Lx, m);
        else update(pos, i*2+2, m, Rx);
        val[i] = merge(val[i*2+1], val[i*2+2]);
    }
    void update(int i)
    {
        update(i, 0, 0, size);
    }
    node query(int l, int r, int i, int Lx, int Rx)
    {
        if(Rx <= l || Lx >= r) return {0,0,0,0,0,0};
        if(Lx >= l && Rx <= r) return val[i];
        int m = (Rx+Lx)/2;
        return merge(query(l,r,i*2+1,Lx,m), query(l,r,i*2+2,m,Rx));
    }

    int query(int l, int r)
    {
        return query(l, r, 0, 0, size).abc;
    }
};

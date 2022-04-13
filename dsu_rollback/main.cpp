struct dsuq
{
    int t, x, v;
};
struct DSU
{
    vector<int> size, p, c;
    int comp;
    bool ok=1;
    void build(int n)
    {
        size = vector<int>(n, 1);
        c = vector<int>(n, 0);
        p = vector<int>(n);
        iota(p.begin(), p.end(), 0);
        comp = n;
    }
    stack<stack<dsuq>> s;
    pair<int,int> get(int x)
    {
        if(p[x] != x)
        {
            auto par = get(p[x]);
            par.second ^= c[x];
            return par;
        }
        return {x,c[x]};
    }
    void save()
    {
        s.push(stack<dsuq>());
    }
    void rollback()
    {
        stack<dsuq> s2 = s.top(); s.pop();
        while(s2.size())
        {
            dsuq q = s2.top(); s2.pop();
            if(q.t==0) p[q.x]=q.v;
            if(q.t==1) size[q.x]=q.v;
            if(q.t==2) c[q.x]=q.v;
            if(q.t==3) ok=q.v;
        }
    }
    void unite(int a, int b)
    {
        auto par=get(a),par2=get(b);
        a=par.first, b=par2.first;
        bool d=par.second, d2=par2.second;
        if(a==b)
        {
            if(d^d2) return;
            s.top().push({3, ok, ok});
            ok=0;
            return;
        }
        if(size[a] > size[b]) swap(a, b);
        s.top().push({0, a, p[a]});
        s.top().push({1, b, size[b]});
        s.top().push({2, a, c[a]});
        p[a] = b;
        size[b] += size[a];
        c[a]=d^d2^1;
    }
};

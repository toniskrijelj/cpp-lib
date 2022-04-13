struct dsuq
{
    int t, x, v;
};
int sz[mxN], p[mxN];
void setup()
{
    fill(sz,sz+mxN,0);
    iota(p,p+mxN,0);
}
stack<stack<dsuq>> stk;
void save()
{
    stk.push(stack<dsuq>());
}
void rollback()
{
    if(stk.empty()) return;
    stack<dsuq> s = stk.top(); stk.pop();
    while(s.size())
    {
        dsuq q = s.top(); s.pop();
        if(q.t==0) p[q.x]=q.v;
        if(q.t==1) sz[q.x]=q.v;
    }
}
int get(int x)
{
    if(p[x] != x) return get(p[x]);
    return x;
}
void unite(int a, int b)
{
    a=get(a),b=get(b);
    if(a==b) return;
    if(sz[a]>sz[b]) swap(a, b);
    if(stk.size()) stk.top().push({0, a, a});
    if(stk.size()) stk.top().push({1, b, sz[b]});
    p[a] = b;
    sz[b] += sz[a];
}

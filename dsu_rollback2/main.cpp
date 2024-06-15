struct dsuq
{
    int t, x, v;
};
int sz[mxN], p[mxN];
void setup()
{
    fill(sz,sz+mxN,1);
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
    if(p[x]^x) return get(p[x]);
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

///complete version control
int k, val[mxM];
int* ptr[mxM];
void upd(int &a, int b)
{
    ptr[k]=&a;
    val[k]=a;
    k++;
    a=b;
}
int nw, sz[mxN], p[mxN], vs[mxN];
pair<int,int> pre[mxM];
int get(int x)
{
    while(x^p[x]) x=p[x];
    return x;
}
void unite(int u, int v)
{
    u=get(u), v=get(v);
    if(u==v) return;
    if(sz[u]>sz[v]) swap(u,v);
    pre[nw]={vs[u],vs[v]};
    upd(p[u],v);
    upd(sz[v],sz[v]+sz[u]);
    upd(vs[v],nw++);
}

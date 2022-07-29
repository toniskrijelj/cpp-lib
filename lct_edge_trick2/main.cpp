#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<ll,null_type,less<ll>,rb_tree_tag,tree_order_statistics_node_update> order_set;
//mt19937 mt_rand(chrono::high_resolution_clock::now().time_since_epoch().count());
//uniform_int_distribution<int> gen; ///(min, max)
//int random() {return gen(mt_rand);}
const int mxN = 3e5+50000;
const int mod = 1e9+9;
const int mxlogN = 20;
const int mxK = 26;
const ll inf = 1e9;
const int K=600;
int p[mxN], ch[mxN][2];
bool tag[mxN];
pair<int,int> mn[mxN];
int val[mxN], mne[mxN];
pair<int,int> min(const pair<int,int> &l, const pair<int,int> &r)
{
    if(l.first<r.first) return l;
    return r;
}
///tags
void flip(int x)
{
    swap(ch[x][0],ch[x][1]);
    tag[x]^=1;
}
/*
void min_eq(int x, int y)
{
    mne[x]=min(mne[x],y);
    val[x]=min(val[x],y);
}*/
void push(int x)
{
    if(tag[x])
    {
        flip(ch[x][0]), flip(ch[x][1]);
        tag[x]=0;
    }
    /*if(mne[x]<inf)
    {
        min_eq(ch[x][0],mne[x]);
        min_eq(ch[x][1],mne[x]);
        mne[x]=inf;
    }*/
}
void recalc(int x)
{
    //mn[x]={val[x],x};
    //if(ch[x][0]) mn[x]=min(mn[x],mn[ch[x][0]]);
    //if(ch[x][1]) mn[x]=min(mn[x],mn[ch[x][1]]);
}
int side(int x)
{
    if(ch[p[x]][0]==x) return 0;
    if(ch[p[x]][1]==x) return 1;
    return -1;
}
void clear_path(int x)
{
    if(~side(x)) clear_path(p[x]);
    push(x);
}
void rotate(int x)
{
    int y=p[x], z=p[y], dx=side(x), dy=side(y), B=ch[x][dx^1];
    if(B) p[B]=y;
    if(~dy) ch[z][dy]=x;
    p[x]=z, p[y]=x;
    ch[x][dx^1]=y, ch[y][dx]=B;
    recalc(y), recalc(x);
}
void splay(int x)
{
    clear_path(x);
    while(~side(x))
    {
        int y=p[x];
        if(!~side(y)) rotate(x);
        else if(side(x)==side(y)) rotate(y), rotate(x);
        else rotate(x), rotate(x);
    }
}
void access(int x)
{
    splay(x);
    ch[x][1]=0;
    recalc(x);
    while(p[x])
    {
        int y=p[x];
        splay(y);
        ch[y][1]=x;
        recalc(y);
        rotate(x);
    }
}
int find_root(int x)
{
    access(x);
    while(ch[x][0]) x=ch[x][0];
    splay(x);
    return x;
}
void change_root(int x)
{
    access(x);
    flip(x);
}
void link(int x, int y)
{
    change_root(x);
    p[x]=y;
}
void cut(int x, int y)
{
    change_root(x);
    access(y);
    ch[y][0]=0;
    recalc(y);
    p[x]=0;
}
int find_lca(int x, int y)
{
    access(x);
    access(y);
    splay(x);
    if(!p[x]) return x;
    return p[x];
}
bool connected(int x, int y)
{
    return find_root(x)==find_root(y);
}
/*pair<int,int> query(int u, int v)
{
    int lca=find_lca(u,v);
    pair<int,int> ret={val[lca],lca};
    if(u!=lca)
    {
        access(u);
        access(lca);
        splay(u);
        if(mn[u].first<ret.first) ret=mn[u];
    }
    if(v!=lca)
    {
        access(v);
        access(lca);
        splay(v);
        if(mn[v].first<ret.first) ret=mn[v];
    }
    return ret;
}*/
struct edge
{
    int u,v,id;
    int other(int i)
    {
        return u^v^i;
    }
}es[mxN];
void init(int x, int y)
{
    val[x]=y;
    mne[x]=inf;
}
void initE(int x, int y)
{
    init(es[x].id,y);
}
void add_edge(int e)
{
    link(es[e].u,es[e].id);
    link(es[e].v,es[e].id);
}
void cut_edge(int e)
{
    cut(es[e].u,es[e].id);
    cut(es[e].v,es[e].id);
}
void query2(int u, int v)
{
    int lca=find_lca(u,v);
    if(u!=lca)
    {
        access(u);
        access(lca);
        splay(u);
        //min_eq(a,c);
    }
    //val[lca]=min(val[lca],c);
    if(v!=lca)
    {
        access(v);
        access(lca);
        splay(v);
        //min_eq(b,c);
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m; cin >> n >> m;
    for(int i=1; i<=n; i++) init(i,inf);
    for(int i=1; i<n; i++)
    {
        int u,v; cin >> u >> v;
        es[i]={u,v,i+n};
        initE(i,inf);
        add_edge(i);
    }
}

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
const int mxN = 8e5+50000;
const int mod = 1e9+9;
const int mxlogN = 20;
const int mxK = 26;
const ll inf = 1e9;
const int K=600;
int p[mxN], ch[mxN][2];
bool tag[mxN];
int add[mxN], val2[mxN], val[mxN], sum[mxN];
int sbs[mxN];
pair<int,int> mn[mxN];
pair<int,int> min(const pair<int,int> &l, const pair<int,int> &r)
{
    if(l.first<r.first) return l;
    return r;
}
///SET mn[0] to inf
int n;
void recalc(int x)
{
    mn[x]={val[x],x};
    sum[x]=val2[x];
    if(x>n) sbs[x]=1;
    else sbs[x]=0;
    if(ch[x][0]) mn[x]=min(mn[x],mn[ch[x][0]]),sbs[x]+=sbs[ch[x][0]],sum[x]+=sum[ch[x][0]];
    if(ch[x][1]) mn[x]=min(mn[x],mn[ch[x][1]]),sbs[x]+=sbs[ch[x][1]],sum[x]+=sum[ch[x][1]];

}
int side(int x)
{
    if(ch[p[x]][0]==x) return 0;
    if(ch[p[x]][1]==x) return 1;
    return -1;
}
void flip(int x)
{
    swap(ch[x][0],ch[x][1]);
    tag[x]^=1;
}
void push(int x);
void ADD(int x, int v)
{
    if(x>n) val2[x]+=v;
    sum[x]+=v*sbs[x];
    add[x]+=v;
    //if(x) push(x);
}
void push(int x)
{
    if(tag[x])
    {
        flip(ch[x][0]), flip(ch[x][1]);
        tag[x]=0;
    }
    if(add[x])
    {
        if(ch[x][0]) ADD(ch[x][0],add[x]);
        if(ch[x][1]) ADD(ch[x][1],add[x]);
        add[x]=0;
    }
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
int c=0;
void link(int x, int y)
{
    change_root(x);
    p[x]=y;
    c++;
}
void cut(int x, int y)
{
    change_root(x);
    access(y);
    ch[y][0]=0;
    recalc(y);
    p[x]=0;
    c--;
}
int find_lca(int x, int y)
{
    access(x);
    access(y);
    splay(x);
    if(!p[x]) return x;
    return p[x];
}
pair<int,int> query(int u, int v)
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
}
int query2(int u, int v)
{
    int lca=find_lca(u,v);
    int ans=0;
    access(u);
    ans+=sum[u];
    access(v);
    ans+=sum[v];
    access(lca);
    ans-=sum[lca];
    lca=ch[lca][0];
    if(lca) ans-=sum[lca];
    return ans;
}
void update(int x, int y, int v)
{
    int lca=find_lca(x,y);
    if(x!=lca)
    {
        access(x);
        access(lca);
        splay(x);
        ADD(x,v);
    }
    if(y!=lca)
    {
        access(y);
        access(lca);
        splay(y);
        ADD(y,v);
    }
    int temp=ch[lca][0];
    ch[lca][0]=0;
    ADD(lca,v);
    push(lca);
    ch[lca][0]=temp;
}
bool connected(int x, int y)
{
    return find_root(x)==find_root(y);
}
int U[mxN], V[mxN];
void add_edge(int x)
{
    int y=x+n;
    mn[y]={x,y};
    val[y]=x;
    sbs[y]=1;
    link(y,U[x]);
    link(V[x],y);
}
void rem_edge(int x)
{
    int y=x+n;
    cut(y,U[x]);
    cut(V[x],y);
}
int who[mxN];
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int m; cin >> n >> m;
    for(int i=0; i<=n; i++)
    {
        mn[i]={inf,inf};
        val[i]=inf;
    }
    for(int i=1; i<=m; i++) cin >> U[i] >> V[i];
    ll ans=0;
    for(int l=1, r=1; l<=m; l++)
    {
        while(r<=m)
        {
            if(!connected(U[r],V[r])) add_edge(r++);
            else
            {
                if(query2(U[r],V[r])) break;
                auto par=query(U[r],V[r]);
                who[par.first]=r;
                update(U[r],V[r],+1);
                r++;
            }
        }
        //cout << "l " << l << " r " << r << "\n";
        ans+=r-l;
        if(who[l])
        {
            int e=who[l];
            update(U[e],V[e],-1);
            rem_edge(l);
            add_edge(e);
        }
        else rem_edge(l);
    }
    cout << ans << "\n";
}
/*
4+3+2+1
*/

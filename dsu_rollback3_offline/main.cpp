///https://codeforces.com/contest/2104/submission/321550311
#if __has_include("pch.hpp")
#include "pch.hpp"
#else
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#endif
using namespace std;
//using namespace atcoder;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
using namespace __gnu_pbds;
typedef tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update> order_set;
mt19937_64 mt_rand(chrono::high_resolution_clock::now().time_since_epoch().count());
//ld rand(ld a, ld b) {uniform_real_distribution<ld> uni(a, b); return uni(mt_rand);}
//const ld PI=3.141592653589793238462643383279;
const int mxN=1e6+50000;
const int mod=1e9+7;
const int mxlogN=19;
const ll inf=1e18;
const int iinf=1e9;
const int K=26;

vector<pair<int*,int>> vs;
int sz[mxN], p[mxN], pty[mxN], ans;
void build(int n)
{
    ans=n&1;
    for(int i=0; i<mxN; i++) sz[i]=1, p[i]=i;
}
vector<int> sv;
void save()
{
    sv.push_back(vs.size());
}
void rollback()
{
    while((int)vs.size()>(int)sv.back())
    {
        (*vs.back().first)=vs.back().second;
        vs.pop_back();
    }
    sv.pop_back();
}
pair<int,int> get(int x)
{
    if(p[x]==x) return {x,0};
    auto [par,xr]=get(p[x]);
    return {par,xr^pty[x]};
}
void updv(int& p, int v)
{
    vs.push_back({&p,p});
    p=v;
}
void unite(int a, int b)
{
    auto [atm,ptyA]=get(a);
    auto [btm,ptyB]=get(b);
    a=atm, b=btm;
    if(sz[a]>sz[b]) swap(a, b);
    if(a==b)
    {
        if(ptyA^ptyB) updv(ans,ans^1);
        return;
    }
    updv(p[a],b);
    updv(sz[b],sz[b]+sz[a]);
    updv(pty[a],ptyA^ptyB^1);
}
struct qry
{
    int l, r, u, v;
};
int qr[mxN];
void print_ans(int i)
{
    if(i)
    {
        if(qr[i]%3==0) cout << "0 ";
        if(qr[i]%3==1) cout << "1 ";
        if(qr[i]%3==2) cout << 1+ans << " ";
    }
}
void solve(int l, int r, vector<qry>& qs) //[l,r]
{
    if(qs.empty())
    {
        for(int i=l; i<=r; i++) print_ans(i);
        return;
    }
    vector<qry> qsL, qsR;
    int m=(l+r)/2;
    save();
    for(auto q:qs) if(q.l<=l&&r<=q.r) unite(q.u,q.v);
    for(auto q:qs) if(!(q.l<=l&&r<=q.r))
    {
        if(q.l<=m&&q.r>=l) qsL.push_back(q);
        if(q.l<=r&&q.r>=m+1) qsR.push_back(q);
    }
    if(l==r) print_ans(l);
    else
    {
        solve(l,m,qsL);
        solve(m+1,r,qsR);
    }
    rollback();
}
vector<qry> qs;
map<pair<int,int>,int> mp;
void upd_edge(int u, int v, int p, int l)
{
    auto par=make_pair(u,v);
    if(mp.count(par))
    {
        qs[mp[par]].r=p-1;
        mp.erase(par);
    }
    else
    {
        qs.push_back({p,l,u,v});
        mp[par]=qs.size()-1;
    }
}
int g[mxN];
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);


    int n,q; cin >> n >> q;
    for(int i=1; i<=n; i++)
    {
        cin >> g[i];
        upd_edge(i,g[i],0,q);
    }
    for(int i=1; i<=q; i++)
    {
        int x, y, k; cin >> x >> y >> k;
        upd_edge(x,g[x],i,q);
        g[x]=y;
        upd_edge(x,g[x],i,q);
        qr[i]=k;
    }
    build(n);
    solve(0,q,qs);
}

/*
int* pt[mxN*3], vt[mxN*3], wh;
int sz[mxN], p[mxN], ans;
void build(int n)
{
    ans=n;
    for(int i=0; i<mxN; i++) sz[i]=1, p[i]=i;
}
vector<int> sv;
void save()
{
    sv.push_back(wh);
}
void rollback()
{
    while(wh>(int)sv.back())
    {
        wh--;
        (*pt[wh])=vt[wh];
    }
    sv.pop_back();
}
void updv(int& p, int v)
{
    pt[wh]=&p;
    vt[wh]=p;
    wh++;
    p=v;
}
*/

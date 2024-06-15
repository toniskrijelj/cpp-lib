///https://codeforces.com/contest/893/submission/136369160
struct segTree
{
    vector<vector<int>> a;
    int sz;
    void build(int n, vector<int> &v, int i, int Lx, int Rx)
    {
        if(Rx-Lx==1)
        {
            if(Lx<n) a[i].push_back(v[Lx]);
            return;
        }
        int m = (Lx+Rx)/2;
        build(n,v,i*2+1,Lx,m);
        build(n,v,i*2+2,m,Rx);
        merge(a[i*2+1].begin(),a[i*2+1].end(),a[i*2+2].begin(),a[i*2+2].end(),back_inserter(a[i]));
    }
    void build(int n, vector<int> &v)
    {
        sz=1;
        while(sz<n) sz<<=1;
        a=vector<vector<int>>(sz<<1);
        build(n,v,0,0,sz);
    }
    int solve(int l, int r, int k, bool g, int i, int Lx, int Rx)
    {
        if(Rx<=l || Lx>=r) return 0;
        if(Lx>=l && Rx<=r)
        {
            if(!g)
            {
                int L=-1,R=a[i].size();
                while(R-L>1)
                {
                    int M=(L+R)/2;
                    if(a[i][M]<k) L=M;
                    else R=M;
                }
                return R;
            }
            else
            {
                int L=-1,R=a[i].size();
                while(R-L>1)
                {
                    int M=(L+R)/2;
                    if(a[i][M]>k) R=M;
                    else L=M;
                }
                return (int)a[i].size()-R;
            }
        }
        int m=(Lx+Rx)/2;
        return solve(l,r,k,g,i*2+1,Lx,m)+solve(l,r,k,g,i*2+2,m,Rx);
    }
    int solve(int l, int r, int k, bool g) { return solve(l,r,k,g,0,0,sz); }
};
https://codeforces.com/contest/1601/problem/D
pair<int,int> arr[mxN];
vector<int> a[mxN];
int sz;
void build2(int n, int i=1, int lx=0, int rx=sz)
{
    a[i].clear();
    if(rx-lx==1)
    {
        if(lx<n) a[i].push_back(arr[lx].second);
        return;
    }
    int m=lx+rx>>1;
    build2(n,i<<1,lx,m);
    build2(n,i<<1|1,m,rx);
    merge(a[i<<1].begin(),a[i<<1].end(),
          a[i<<1|1].begin(),a[i<<1|1].end(),
         back_inserter(a[i]));
}
void build(int n)
{
    sz=1;
    while(sz<n) sz<<=1;
    build2(n);
}
int qry(int l, int r, int v, int i=1, int lx=0, int rx=sz)
{
    if(rx<=l || lx>=r) return 0;
    if(lx>=l && rx<=r) return a[i].end()-lower_bound(a[i].begin(),a[i].end(),v);
    int m=lx+rx>>1;
    return qry(l,r,v,i<<1,lx,m)+qry(l,r,v,i<<1|1,m,rx);
}


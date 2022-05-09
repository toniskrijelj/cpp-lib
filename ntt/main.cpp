const int root=3,mod=998244353,root_inv=332748118;
ll powb(ll a, ll x)
{
    ll ret=1;
    a%=mod;
    while(x)
    {
        if(x&1)ret=ret*a%mod;
        x>>=1;
        a=a*a%mod;
    }
    return ret;
}
ll inv(ll x)
{
    return powb(x, mod-2);
}
void ntt(vector<int>& a, const vector<int>& rev, bool f)
{
    int n=a.size();
    for(int i=0; i<n; i++)
        if(i<rev[i])
            swap(a[i],a[rev[i]]);
    for(int mid=1; mid<n; mid<<=1)
    {
        int len=mid<<1;
        ll Wn=powb(f?root_inv:root,(mod-1)/len);
        for(int j=0; j<n; j+=len)
        {
            ll w=1;
            for(int k=0; k<mid; k++)
            {
                ll x=a[j+k],y=w*a[j+k+mid]%mod;
                a[j+k]=(x+y)%mod;
                a[j+k+mid]=(x-y+mod)%mod;
                w=w*Wn%mod;
            }
        }
    }
    if(f)
    {
        ll invn=inv(n);
        for(int& x : a) x=invn*x%mod;
    }
}
vector<int> multiply(vector<int> a, vector<int> b)
{
    int n=1,lg=0;
    while(n<(int)a.size()+(int)b.size()) n<<=1,lg++;
    vector<int> rev(n);
    a.resize(n), b.resize(n);
    for(int i=0; i<n; i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
    ntt(a,rev,0);
    ntt(b,rev,0);
    for(int i=0; i<n; i++) a[i]=(ll)a[i]*b[i]%mod;
    ntt(a,rev,1);
    return a;
}
int solve(int n, const vector<int> &a, int k) ///DNQ NTT
{
    vector<vector<int>> poly(n);
    for(int i=0; i<n; i++) poly[i]={1,a[i]};
    for(int len=1; len<n; len*=2)
    {
        for(int i=0; i+len<n; i+=len*2)
        {
            poly[i]=multiply(poly[i],poly[i+len]);
        }
    }
    return poly[0][k];
}

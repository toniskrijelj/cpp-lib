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
ll f[mxN], finv[mxN];
ll chose(ll a, ll b)
{
    if(a<0||a>b) return 0;
    return f[b]*finv[a]%mod*finv[b-a]%mod;
}

    f[0]=1;
    for(int i=1; i<mxN; i++) f[i]=f[i-1]*i%mod;
    finv[mxN-1]=inv(f[mxN-1]);
    for(int i=mxN-2; i>=0; i--) finv[i]=finv[i+1]*(i+1)%mod;



bool prime(int x)
{
    for(int i=2; i*i<=x; i++)
    {
        if(x%i==0)return 0;
    }
    return 1;
}

vector<int> pf(int x)
{
    vector<int> p;
    for(int i=2; i*i<=x; i++)
    {
        if(x%i==0)
        {
            p.push_back(i);
            while(x%i==0) x/=i;
        }
    }
    if(x>1) p.push_back(x);
    return p;
}

int p[mxN];
void sieve()
{
    for(int i=2; i<mxN; i++)
    {
        if(!p[i])
        for(int j=i; j<mxN; j+=i)
        {
            if(!p[j]) p[j]=i;
        }
    }
}
vector<int> pf(int x)
{
    vector<int> ans;
    while(x>1)
    {
        if(ans.empty()||ans.back()!=p[x]) ans.push_back(p[x]);
        x/=p[x];
    }
    return ans;
}

    f[0]=1;
    for(int i=1; i<mxN; i++) f[i]=f[i-1]*i%mod;
    finv[mxN-1]=inv(f[mxN-1]);
    for(int i=mxN-2; i>=0; i--) finv[i]=finv[i+1]*(i+1)%mod;


mt19937 mt_rand(chrono::high_resolution_clock::now().time_since_epoch().count());

v.erase(unique(v.begin(), v.end()), v.end());

double st=clock();
while ((clock()-st)/CLOCKS_PER_SEC<3.5)

FILE* f1 = fopen("C:\\Users\\toni\\Desktop\\2019-2020-sio1-problems\\03_smestaj\\testcases\\50.out", "r");
FILE* f2 = fopen("C:\\Users\\toni\\Desktop\\2019-2020-sio1-problems\\03_smestaj\\testcases\\50a.out", "r");


ll _ceil(ll, ll);
ll _floor(ll a, ll b) { return b < 0 ? _floor(-a, -b) : a < 0 ? -_ceil(-a, b) : a / b; }
ll _ceil(ll a, ll b) { return b < 0 ? _ceil(-a, -b) : a < 0 ? -_floor(-a, b) : (a + b - 1) / b; }

ll gcd(ll a, ll b, ll& x, ll& y)
{
    if(!b)
    {
        x=1;
        y=0;
        return a;
    }
    ll x1,y1;
    ll d=gcd(b,a%b,x1,y1);
    x=y1;
    y=x1-y1*(a/b);
    return d;
}
/// all in form
///(a-ky/d, b+kx/d), ax+by=gcd
#pragma GCC target("popcnt")

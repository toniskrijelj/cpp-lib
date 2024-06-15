void solve(ll a, ll p, ll p2, ll n, ll m) //f(a)=x*f(a+1) + y*f(a) + z*f(a-1) + z;
{
    if(a>m) return;
    p=(p%mod+mod)%mod;
    p2=(p2%mod+mod)%mod;
    ll x=(m-a)*inv(m)%mod*inv(n-1)%mod;
    ll y=(m-a)*(n-2)%mod*inv(m)%mod*inv(n-1)%mod;
    ll z=(a)*inv(m)%mod;
    //cout << "bake " << a << " " << p << " " << p2 << " " << x << " " << y << " " << z << "\n";
    /*
    f(a)=x*f(a+1)+y*f(a)+z*p*f(a)+z*p2+z;
    f(a)-y*f(a)-z*p*f(a) = x*f(a+1)+z*p2+z;
    (1-y-z*p)*f(a)=x*f(a+1)+z*p2+z;
    f(a)=(x*f(a+1)+z*p2+z)/(1-y-z*p);
    */
    solve(a+1,x*inv(1-y-z*p)%mod,(z*p2%mod-z)*inv(1-y-z*p)%mod,n,m);
    f[a]=((f[a+1]*(x*inv(1-y-z*p)%mod)%mod + (z*p2%mod-z)*inv(1-y-z*p)%mod)%mod+mod)%mod;
}

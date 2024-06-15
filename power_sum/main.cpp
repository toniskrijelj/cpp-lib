//https://codeforces.com/contest/622/submission/188334027
ll dp[mxN];
void solve(int n, int k) /// O(k^2)
{
    dp[0]=n;
    for(int i=1; i<=k; i++)
    {
        ll ans=(powb(n+1,i+1)-1+mod)%mod;
        for(int l=0; l<i; l++) ans=(ans+mod-chose(l,i+1)*dp[l]%mod)%mod;
        dp[i]=ans*inv(i+1)%mod;
    }
}
ll solve(int x, int k) /// O(klogMOD), optimize to O(k) bez
{
    int n=k+2;
    vector<ll> F(n+1,0); ///data points
    for(int i=1; i<=n; i++) F[i]=(F[i-1]+powb(i,k))%mod;
    if(x<=n) return F[x];
    ll mul=1, ans=0;
    for(int i=1; i<=n; i++) mul=mul*(x-i)%mod;
    for(int i=1; i<=n; i++)
    {
        ll cur=F[i]*mul%mod*inv(x-i)%mod*finv[i-1]%mod*finv[n-i]%mod;
        if((n-i)&1) ans=(ans+mod-cur)%mod;
        else ans=(ans+cur)%mod;
    }
    return ans;
}

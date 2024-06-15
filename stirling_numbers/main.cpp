///https://codeforces.com/contest/1644/submission/164042287
bool done[mxN];
vector<int> ans[mxN];
ll stirling(int k, int n)
{
    if(done[n]) return ans[n][k];
    done[n]=1;
    vector<int> a(n+1),b(n+1);
    for(int i=0; i<=n; i++)
    {
        a[i]=powb(-1,i)*inv(f[i])%mod*powb(i,n)%mod;
        b[i]=inv(f[i]);
    }
    ans[n]=multiply(a,b);
    for(int i=1; i<=n; i+=2) ans[n][i]=(mod-ans[n][i])%mod;
    //cout << "gotov\n";
    return stirling(k,n);
}

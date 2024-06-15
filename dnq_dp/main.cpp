///C(a,c)+C(b,d) <= C(a,d)+C(b,c)
ll dp[mxN], dp2[mxN];
ll cost(int l, int r)
{
    if(l>r) return 0;
    ///
}
int pos[mxN];
void solve(int l, int r, int optl, int optr)
{
    if(l>r) return;
    int m=(l+r)/2, opt=m-1;
    ll best=dp[m];
    for(int k=optl; k<=min(m-1,optr); k++)
    {
        ll cur=dp[k]+cost(k,m);
        if(cur<=best)
        {
            best=cur;
            opt=k;
        }
    }
    dp2[m]=best;
    pos[m]=opt;
    solve(l,m-1,optl,opt);
    solve(m+1,r,opt,optr);
}
/*
for(int i=1; i<=n; i++) dp[i]=cost(0,i);
while(--k)
{
    solve(1,n,1,n);
    for(int i=1; i<=n; i++) dp[i]=dp2[i];
}
*/


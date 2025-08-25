///https://codeforces.com/contest/2120/submission/325614107
//smanjuje najvecih m, povecava najmanjih m
ll a[mxN];
int n;
void f(ll m)
{
    ll x=m;
    for(int i=n-1; i; i--)
    {
        if((a[i]-a[i-1])*(n-i)<x) x-=(a[i]-a[i-1])*(n-i);
        else
        {
            ll t=x/(n-i);
            ll r=x-t*(n-i);
            a[i]-=t;
            for(int j=i+1; j<n; j++) a[j]=a[i];
            for(int j=i; j<i+r; j++) a[j]--;
            break;
        }
    }
    x=m;
    for(int i=0; i<n; i++)
    {
        if((a[i+1]-a[i])*(i+1)<x) x-=(a[i+1]-a[i])*(i+1);
        else
        {
            ll t=x/(i+1);
            ll r=x-t*(i+1);
            a[i]+=t;
            for(int j=i-1; j>=0; j--) a[j]=a[i];
            for(int j=i; j>i-r; j--) a[j]++;
            break;
        }
    }
}

#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<ll,null_type,less_equal<ll>,rb_tree_tag,tree_order_statistics_node_update> order_set;
mt19937 mt_rand(chrono::high_resolution_clock::now().time_since_epoch().count());
//uniform_int_distribution<int> gen; ///(min, max)
//int random() {return gen(mt_rand);}
const int mxN=5e5+5;
const int mod=1e9+7;
const int mxlogN=40;
const int mxK=26;
const ll inf=1e18;
const int K=600;
ll a[mxN],b[mxN];
int solve(int n, int k, ll m, bool p=0)
{
    priority_queue<ll> pqA, pqB; ///pqB je minimum
    int cnt=0;
    ll dp=0;
    for(int i=0; i<n; i++)
    {
        pqA.push(a[i]+m);
        if(pqB.size())
        {
            ll A=pqA.top()+b[i];
            ll B=b[i]-(-pqB.top());
            if(max(A,B)>=0)
            {
                if(A>=B)
                {
                    cnt++;
                    pqA.pop();
                    dp+=A;
                }
                else
                {
                    pqB.pop();
                    pqB.push(-b[i]);
                    dp+=B;
                }
            }
        }
        else
        {
            ll A=pqA.top()+b[i];
            if(A>=0)
            {
                cnt++;
                pqA.pop();
                dp+=A;
                pqB.push(-b[i]);
            }
        }
    }
    if(p) cout << -(dp-cnt*m) << "\n";
    return cnt;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k; cin >> n >> k;
    for(int i=0; i<n; i++) cin >> a[i], a[i]=-a[i];
    for(int i=0; i<n; i++) cin >> b[i], b[i]=-b[i];

    ll l=0, r=2e9;
    while(r-l>1)
    {
        int m=(l+r)/2;
        if(solve(n,k,m)) r=m;
        else l=m;
    }
    solve(n,k,r,1);
}
/*

*/

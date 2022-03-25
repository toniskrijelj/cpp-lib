
struct query
{
    int l,r,i;
    bool operator<(const query& q) const
    {
        return r<q.r;
    }
};
vector<query> qrs[K];
int q; cin >> q;
for(int i = 0; i < q; i++)
{
    int l, r; cin >> l >> r;
    qrs[l/K].push_back({l,r,i});
}
for(int i = 0; i < K; i++)
{
    sort(qrs[i].begin(), qrs[i].end());
    int L=K*(i+1)-1, R=K*(i+1);
    ll ans=0;
    for(auto q : qrs[i])
    {
        int l=q.l,r=q.r;
        if(r<=L)
        {
            for(int i = l; i <= r; i++)
            {
                ans+=mp2[p[i]-x];
                mp2[p[i]]++;
            }
            b[q.i]=ans;
            ans=0;
        }
        else
        {
            while(R<=r)
            {
                ans+=mp[p[R]-x];
                mp[p[R]]++;
                R++;
            }
            int L2=L;
            while(L2>=l)
            {
                L2--;
                ans+=mp[p[L2]+x];
                mp[p[L2]]++;
            }
            ///b[q.i]=ans;
            while(L2<L)
            {
                mp[p[L2]]--;
                ans-=mp[p[L2]+x];
                L2++;
            }
        }
    }
}
for(int i = 0; i < q; i++) cout << b[i] << "\n";

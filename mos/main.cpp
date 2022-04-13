
struct query
{
    int l,r,i;
    bool operator<(const query& q) const
    {
        return r<q.r;
    }
};
vector<query> qrs[K];
int a[mxN], b[mxN];
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
    for(auto q : qrs[i])
    {
        int l=q.l,r=q.r;
        if(r<=L)
        {
            for(int i = l; i <= r; i++)
            {
            }
            int ans=-1;
            b[q.i]=ans;
        }
        else
        {
            while(R<=r) add(R++);
            int L2=L;
            while(L2>=l) add(L2--);
            int ans=-1;
            b[q.i]=ans;
            while(L2<L) rem(++L2);
        }
    }
}
for(int i = 0; i < q; i++) cout << b[i] << "\n";

///https://codeforces.com/contest/893/submission/136369160

struct segTree
{
    struct node
    {
        vector<pair<int, int>> arr;
    };
    int size;
    vector<node> val; /// minimum, sum count
    void build(int n, int i, int Lx, int Rx)
    {
        if(Rx-Lx==1)
        {
            if(Lx < n) val[i].arr = {v[Lx]};
            return;
        }
        int m = (Lx+Rx)/2;
        build(n, i*2+1, Lx, m);
        build(n, i*2+2, m, Rx);

        int p1 = 0, p2 = 0;
        while(p1 < val[i*2+1].arr.size() && p2 < val[i*2+2].arr.size())
        {
            if(val[i*2+1].arr[p1].first <= val[i*2+2].arr[p2].first)
            {
                val[i].arr.push_back(val[i*2+1].arr[p1]);
                p1++;
            }
            else
            {
                val[i].arr.push_back(val[i*2+2].arr[p2]);
                p2++;
            }
        }
        while(p1 < val[i*2+1].arr.size()) val[i].arr.push_back(val[i*2+1].arr[p1++]);
        while(p2 < val[i*2+2].arr.size()) val[i].arr.push_back(val[i*2+2].arr[p2++]);

        for(int j = 1; j < val[i].arr.size(); j++)
        {
            val[i].arr[j].second = min(val[i].arr[j].second, val[i].arr[j-1].second);
        }
    }
    void build(int n)
    {
        size = 1;
        while(size < n) size <<= 1;
        val = vector<node>(size << 1);
        build(n, 0, 0, size);
    }
    ll solve(int l, int r, int k, int i, int Lx, int Rx)
    {
        if(Rx <= l || Lx >= r) return 1e9;
        if(Lx >= l && Rx <= r)
        {
            //cout << "da buraz " << Lx << " " << Rx << "\n";
            //for(auto x : val[i].arr) cout << x.first << " " << x.second << ",";
            //cout << "\n";
            int L = -1, R = val[i].arr.size();
            while(R-L>1)
            {
                int M = (L+R)/2;
                if(val[i].arr[M].first <= k) L = M;
                else R = M;
            }
            if(L == -1) return 1e9;
            return val[i].arr[L].second;
        }
        int m = (Lx+Rx)/2;
        return min(solve(l, r, k, i*2+1, Lx, m), solve(l, r, k, i*2+2, m, Rx));
    }

    ll solve(int l, int r, int k)
    {
        return solve(l, r, k, 0, 0, size);
    }
};

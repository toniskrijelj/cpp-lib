void count_sort(vector<int> &p, vector<int> &c)
{
    int n = p.size();
    vector<int> counts(n);
    for(auto x : c)
    {
        counts[x]++;
    }
    vector<int> p_new(n);
    vector<int> pos(n);
    pos[0] = 0;
    for(int i = 1; i < n; i++)
    {
        pos[i] = pos[i - 1] + counts[i - 1];
    }
    for(auto x : p)
    {
        int i = c[x];
        p_new[pos[i]] = x;
        pos[i]++;
    }
    p = p_new;
}
vector<int> suffix_array(string t)
{
    t+="$";
    ll n = t.size();

    vector<int> p(n), c(n);

    vector<pair<char, int>> a(n);
    for(int i = 0; i < n; i++) a[i] = {t[i], i};
    sort(a.begin(), a.end());
    for(int i = 0; i < n; i++) p[i] = a[i].second;

    c[p[0]] = 0;
    for(int i = 1; i < n; i++)
    {
        if(a[i].first == a[i-1].first) c[p[i]] = c[p[i-1]];
        else c[p[i]] = c[p[i-1]] + 1;
    }
    //
    int k = 0;
    while((1 << k) < n)
    {
        for(int i = 0; i < n; i++) p[i]=(p[i]-(1<<k)+n)%n;
        count_sort(p, c);
        vector<int> c_new(n);
        c_new[p[0]] = 0;
        for(int i = 1; i < n; i++)
        {
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1]+(1<<k))%n]};
            pair<int, int> now = {c[p[i]], c[(p[i]+(1<<k))%n]};
            if(now==prev) c_new[p[i]] = c_new[p[i-1]];
            else c_new[p[i]] = c_new[p[i-1]]+1;
        }
        c = c_new;
        k++;
    }
    return p;
}
vector<int> LCP(string t, vector<int>& p)
{
    int n=p.size();
    vector<int> c(n);
    t+="$";
    for(int i = 0; i < n; i++) c[p[i]]=i;
    int k=0;
    vector<int> lcp(n);
    for(int i = 0; i < n-1; i++)
    {
        int pi = c[i];
        int j = p[pi-1];
        while(t[i+k] == t[j+k]) k++;
        lcp[pi] = k;
        k = max(0, k - 1);
    }
    return lcp;
}
void KMP(string &s, vector<int> &kmp)
{
    kmp=vector<int>(s.size(), 0);
    for(int i=1; i<(int)s.size(); i++)
    {
        int t=kmp[i-1];
        while(t)
        {
            if(s[t]==s[i]) break;
            t=kmp[t-1];
        }
        if(s[t]==s[i]) t++;
        kmp[i]=t;
    }
}
void Z(string &s, vector<int> &z)
{
    z=vector<int>(s.size(), 0);
    int r=0, l=0;
    for(int i=1; i<(int)s.size(); i++)
    {
        if(i<r) z[i]=min(z[i-l], r-i);
        while(s[z[i]]==s[z[i]+i]) z[i]++;
        if(i+z[i]>r)
        {
            r=i+z[i];
            l=i;
        }
    }
}

vector<int> manacher(string s)
{
    string t="#";
    for(auto c:s) t+=c, t+="#";
    int n=t.size();
    vector<int> ans(n);
    for(int i=0, j=0; i<n; i++)
    {
        if(2*j-i>=0 && j+ans[j]>i) ans[i]=min(ans[2*j-i], j+ans[j]-i);
        while(i-ans[i]>=0 && i+ans[i]<n && t[i-ans[i]]==t[i+ans[i]]) ans[i]++;
        if(i+ans[i] > j+ans[j]) j=i;
    }
    return ans;
}
//[l,r) substring : ans[l+r] >= r-l;

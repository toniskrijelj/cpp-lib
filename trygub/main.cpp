struct trygub
{
    int base;
    map<int,int> digs;
    void setup(int b)
    {
        digs.clear();
        base=b;
    }
    void add(int a, int b)
    {
        if(!a) return;
        auto it=digs.insert({b,0}).first;
        it->second+=a;
        vector<map<int,int>::const_iterator> todel;
        while(1)
        {
            int t=it->second/base;
            if(!t) break;
            it->second-=t*base;
            if(!it->second) todel.push_back(it);
            if(next(it)==digs.end()||next(it)->first!=b+1)
            digs.insert(next(it),{b+1,0});
            it++; it->second+=t;
            b++;
        }
        if(!it->second) todel.push_back(it);
        for(auto it:todel) digs.erase(it);
    }
    int get(int k)
    {
        auto it=digs.lower_bound(k);
        int ans=0;
        if(it!=digs.end()&&it->first==k) ans=it->second;
        if(it!=digs.begin()&&prev(it)->second<0) ans--;
        return (ans+base)%base;
    }
    int le0()
    {
        if(digs.empty()) return 1;
        return digs.rbegin()->second<0;
    }
    void pop()
    {
        while(digs.size()>1)
        {
            auto [k,c]=*digs.rbegin();
            auto [k2,c2]=*next(digs.rbegin());
            if(k2+1==k&&-c2==base-1&&c==1)
            {
                digs.erase(prev(digs.end()));
                digs.rbegin()->second=1;
            }
            else break;
        }
    }
};

int cnt[mxN];
struct trygub2
{
    set<int> digs;
    int base;
    void setup(int b)
    {
        base=b;
        for(auto x:digs) cnt[x]=0;
        digs.clear();
    }
    void add(int a, int b)
    {
        if(!a) return;
        cnt[b]+=a;
        auto it=digs.insert(b).first;
        vector<set<int>::const_iterator> todel;
        while(1)
        {
            int t=cnt[b]/base;
            if(!t) break;
            if(next(it)==digs.end()||*next(it)!=b+1)
            digs.insert(next(it),b+1);
            cnt[b]-=t*base;
            cnt[b+1]+=t;
            if(!cnt[b]) todel.push_back(it);
            it++, b++;
        }
        if(!cnt[b]) todel.push_back(it);
        for(auto it:todel) digs.erase(it);
    }
    int get(int k)
    {
        auto it=digs.lower_bound(k);
        int ans=cnt[k];
        if(it!=digs.begin()&&cnt[*prev(it)]<0) ans--;
        return (ans+base)%base;
    }
    int le0()
    {
        if(digs.empty()) return 1;
        return cnt[*digs.rbegin()]<0;
    }
    void pop()
    {
        while(digs.size()>1)
        {
            auto k=*digs.rbegin(), k2=*next(digs.rbegin());
            int c=cnt[k],c2=cnt[k2];
            if(k2+1==k&&c==1&&c2==(-base+1))
            {
                digs.erase(prev(digs.end()));
                cnt[k]=0, cnt[k2]=1;
            }
            else break;
        }
    }
};

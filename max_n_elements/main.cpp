multiset<ll> ms;
auto it=ms.end();
ll sum=0, can=0;
void add(ll x)
{
    if(can>ms.size())
    {
        ms.insert(x);
        sum+=x;
        it=ms.begin();
    }
    else
    {
        ms.insert(x);
        if(it!=ms.end()&&x>=*it) sum+=-(*it++)+x;
    }
}
void rem(ll x)
{
    if(it==ms.begin())
    {
        sum-=x;
        ms.erase(ms.find(x));
        it=ms.begin();
    }
    else
    {
        if(it!=ms.end()&&(*it<x||(*it==x&&*prev(it)!=x))) sum+=(*--it)-x;
        ms.erase(ms.find(x));
    }
}
void addnew()
{
    can++;
    if(it!=ms.begin()) sum+=*--it;
}
void remnew()
{
    can--;
    if(it!=ms.end()) sum-=*it++;
}





///old implementation, longer, stress tested
multiset<ll> ms;
auto it=ms.end();
ll sum=0;
int can=0, did=0;
void setup()
{
    it=ms.end();
    can=did=sum=0;
}
void add(ll x)
{
    ms.insert(x);
    if(can==0) return;
    if(did==0)
    {
        sum += x;
        it--;
        did++;
        return;
    }
    if(can==did)
    {
        if(x >= *it)
        {
            sum -= *it;
            sum += x;
            it++;
        }
    }
    else if(x >= *it)
    {
        sum += x;
        did++;
    }
    else
    {
        sum += x;
        it--;
        did++;
    }
}
void rem(ll x)
{
    auto jt = ms.find(x);
    if(did==0)
    {
        ms.erase(jt);
        return;
    }
    if(x < *it || (x==*it && jt!=it))
    {
        ms.erase(jt);
        return;
    } ///x > it || jt==it
    if(jt==it)
    {
        it++;
        ms.erase(jt);
        did--;
        sum -= x;
        if(it!=ms.begin())
        {
            it--;
            did++;
            sum += *it;
        }
        return;
    }
    ms.erase(jt);
    sum -= x;
    if(it!=ms.begin())
    {
        it--;
        sum += *it;
    }
    else did--;
}
void addnew()
{
    can++;
    if(it!=ms.begin())
    {
        it--;
        did++;
        sum+=*it;
    }
}
void remnew()
{
    if(did==can)
    {
        sum-=*it;
        did--;
        it++;
    }
    can--;
}

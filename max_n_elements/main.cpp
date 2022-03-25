
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
    x = -x;
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
    x = -x;
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

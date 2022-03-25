const ld M_PI = acos(-1);

struct point
{
    ll x, y;
    ll cross(const point& b) const
    {
        return x*b.y-y*b.x;
    }
    bool operator<(const point& b) const
    {
        int sign = (y>0||(y==0&&x>0));
        int sign2 = (b.y>0||(b.y==0&&b.x>0)); ///ako se razlikuju
        if(sign!=sign2) return sign>sign2;
        return cross(b)>0;
    }
};

int x[mxN], y[mxN];
point a[mxN];
map<point, int> points;
bool bad()
{
    return 0;
}
void insert(point a, point b)
{
    if(a.cross(b)<0)  ;
}
void erase(point a, point b)
{
    if(a.cross(b)<0)  ;
}
void add(int i)
{
    if(x[i]==0&&y[i]==0)
    {
        return;
    }
    if(++points[a[i]] > 1) return;
    auto it = points.find(a[i]);
    auto jt = (it==points.begin()?prev(points.end()):prev(it));
    auto kt = (next(it)==points.end()?points.begin():next(it));
    if(points.size()>2) erase(jt->first, kt->first);
    if(points.size()>1) insert(jt->first, it->first);
    if(points.size()>1) insert(it->first, kt->first);

}
void rem(int i)
{
    if(x[i]==0&&y[i]==0)
    {
        eq--;
        return;
    }
    if(--points[a[i]] > 0) return;
    auto it = points.find(a[i]);
    auto jt = (it==points.begin()?prev(points.end()):prev(it));
    auto kt = (next(it)==points.end()?points.begin():next(it));
    if(points.size()>2) insert(jt->first, kt->first);
    if(points.size()>1) erase(jt->first, it->first);
    if(points.size()>1) erase(it->first, kt->first);
    points.erase(it);
}

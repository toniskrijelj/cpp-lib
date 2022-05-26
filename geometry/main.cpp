const double PI=acos(-1);
double deg(double dg)
{
    return dg*PI/180.0;
}
cout << 1.0/(1+2*cos(PI/n))*sin(PI/n)*r*r*n << "\n";

struct point
{
    ll x, y;
};
ll cross(const point& a, const point& b)
{
    return a.x*b.y-a.y*b.x;
}
point sub(const point& a, const point& b)
{
    return {a.x-b.x, a.y-b.y};
}
ld dist(const point& a, const point& b)
{
    return sqrt(a.x*b.x+a.y*b.y);
}
ll cross(const point& a, const point& b, const point& c)
{
    return cross(sub(b,a),sub(c,a));
}
ll area(const point& a, const point& b, const point& c)
{
    return abs(cross(a,b,c))/2;
}
ld dist_point_line(const point& p, const point& a, const point& b)
{
    return area(a,b,p)/dist(a,b);
}
bool same_side(const point& a, const point& b, const point& c, const point& p)
{
    ll o=cross(a,b,c);
    ll o2=cross(a,b,p);
    if(!o||!o2) return 1;
    return (o>0)==(o2>0);
}
bool inside(const point& a, const point& b, const point& c, const point& p)
{
    return same_side(a,b,c,p)&&same_side(b,c,a,p)&&same_side(c,a,b,p);
}
bool contains(const vector<point>& poly, const int l, const int r, const point& p)
{
    if(r-l==1) return inside(poly[0], poly[l], poly[r], p);
    int m=(l+r)/2;
    if(cross(poly[0], poly[m], p)>0) return contains(poly, m, r, p);
    else return contains(poly, l, m, p);
}
bool contains(const vector<point>& poly, const point& p)
{
    if(poly.size()<3)
    {
        ll x=poly[0].x,x2=poly[0].x,y=poly[0].y,y2=poly[0].y;
        if(poly.size()==2) x=min(x,poly[1].x), x2=max(x2,poly[1].x), y=min(y,poly[1].y), y2=max(y2,poly[1].y);
        return p.x>=x&&p.x<=x2&&p.y>=y&&p.y<=y2;
    }
    return contains(poly, 1, poly.size()-1, p);
}
void compress(vector<point>& poly)
{
    vector<point> nw;
    int n=poly.size();
    for(int i=0; i<n; i++)
    {
        int sz=nw.size();
        if(sz>=2&&!cross(nw[sz-2],nw[sz-1],poly[i])) nw.pop_back();
        nw.push_back(poly[i]);
    }
    poly=nw;
}

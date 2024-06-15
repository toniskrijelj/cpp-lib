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

struct pt {
    ll x, y; bool b;
};

int orientation(pt a, pt b, pt c) {
    ll v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    if (v < 0) return -1; // clockwise
    if (v > 0) return +1; // counter-clockwise
    return 0;
}

bool cw(pt a, pt b, pt c, bool include_collinear) {
    int o = orientation(a, b, c);
    return o < 0 || (include_collinear && o == 0);
}
bool collinear(pt a, pt b, pt c) { return orientation(a, b, c) == 0; }

void convex_hull(vector<pt>& a, bool include_collinear)
{
    pt p0 = *min_element(a.begin(), a.end(), [](pt a, pt b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });
    sort(a.begin(), a.end(), [&p0](const pt& a, const pt& b) {
        int o = orientation(p0, a, b);
        if (o == 0)
            return (p0.x-a.x)*(p0.x-a.x) + (p0.y-a.y)*(p0.y-a.y)
                < (p0.x-b.x)*(p0.x-b.x) + (p0.y-b.y)*(p0.y-b.y);
        return o < 0;
    });
    if (include_collinear) {
        int i = (int)a.size()-1;
        while (i >= 0 && collinear(p0, a[i], a.back())) i--;
        if(~i) reverse(a.begin()+i+1, a.end());
    }

    vector<pt> st;
    for (int i = 0; i < (int)a.size(); i++) {
        while (st.size() > 1 && !cw(st[st.size()-2], st.back(), a[i], include_collinear))
            st.pop_back();
        st.push_back(a[i]);
    }

   a = st;
}

bool up(int x, int y)
{
    return y>0||(y==0&&x>0);
}
///polar sort
struct point
{
    ll x, y;
    bool up() const {return y>0||(y==0&&x>0);}
    bool operator<(const point& p) const
    {
        if(up()!=p.up()) return up();
        return x*p.y>y*p.x;
    }
    point operator-() const
    {
        return {-x,-y};
    }
};

struct pnt
{
    ll x,y;
    pnt operator-(const pnt& p2) const
    {
        pnt p3=*this;
        p3.x-=p2.x;
        p3.y-=p2.y;
        return p3;
    }
    pnt operator+(const pnt& p2) const
    {
        pnt p3=*this;
        p3.x+=p2.x;
        p3.y+=p2.y;
        return p3;
    }
    pnt operator*(const int& p2) const
    {
        pnt p3=*this;
        p3.x*=p2;
        p3.y*=p2;
        return p3;
    }
    bool operator<(const pnt& p2) const
    {
        if(x^p2.x) return x<p2.x;
        return y<p2.y;
    }
};
ll cross(pnt a, pnt b)
{
    return a.x*b.y-a.y*b.x;
}
ll cross(pnt a, pnt b, pnt c)
{
    return cross(b-a,c-a);
}
ll side(pnt a, pnt b, pnt c)
{
    ll C=cross(a,b,c);
    if(!C) return 0;
    return C/abs(C);
}
bool between(pnt v1, pnt v2, pnt v3)
{
    return v3.x>=min(v1.x,v2.x) && v3.x<=max(v1.x,v2.x) &&
           v3.y>=min(v1.y,v2.y) && v3.y<=max(v1.y,v2.y);
}

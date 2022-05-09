struct frac
{
    ll x,y;
    frac(ll xx, ll yy)
    {
        if(yy<0) xx=-xx, yy=-yy;
        //ll gcd=__gcd(abs(xx),abs(yy));
        x=xx, y=yy;
    }
    bool operator<=(const frac &f) const
    {
        return x*f.y<=f.x*y;
    }
    bool operator<(const frac &f) const
    {
        return x*f.y<f.x*y;
    }
    bool operator==(const frac &f) const
    {
        return x*f.y==f.x*y;
    }
    frac operator*(const frac &f) const
    {
        return {x*f.x, y*f.y};
    }
    frac operator+(const frac &f) const
    {
        return {x*f.y+f.x*y, y*f.y};
    }
};

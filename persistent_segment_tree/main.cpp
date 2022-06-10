int lc[mxM], rc[mxM], sum[mxM], sz=1, m=1;
int update(int l, int r, int x, int i, int Lx=0, int Rx=m)
{
    if(Rx<=l||Lx>=r) return i;
    int nw = sz++;
    if(i!=-1) lc[nw]=lc[i], rc[nw]=rc[i], sum[nw]=sum[i];
    if(Lx >= l && Rx <= r)
    {
        sum[nw]+=x;
        return nw;
    }
    int m=(Lx+Rx)/2;
    lc[nw]=update(l,r,x,lc[i],Lx,m);
    rc[nw]=update(l,r,x,rc[i],m,Rx);
    return nw;
}
int query(int l, int r, int i, int Lx=0, int Rx=m)
{
    if(Rx<=l||Lx>=r||i==-1) return 0;
    if(Lx>=l && Rx<=r) return sum[i];
    int m=(Lx+Rx)>>1;
    return query(l,r,lc[i],Lx,m)+query(l,r,rc[i],m,Rx);
}
int query(int pos, int i, int Lx=0, int Rx=m)
{
    if(i==-1) return 0;
    if(Rx-Lx==1) return sum[i];
    int m=(Lx+Rx)>>1;
    if(pos<m) return sum[i]+query(pos,lc[i],Lx,m);
    else      return sum[i]+query(pos,rc[i],m,Rx);
}
int update(int pos, int x, int i, int Lx=0, int Rx=m)
{
    int nw=sz++;
    if(i!=-1) lc[nw]=lc[i], rc[nw]=rc[i], sum[nw]=sum[i];
    sum[nw]+=x;
    if(Rx-Lx==1) return nw;
    int m=(Lx+Rx)>>1;
    if(pos<m) lc[nw]=update(pos,x,lc[i],Lx,m);
    else rc[nw]=update(pos,x,rc[i],m,Rx);
    return nw;
}

void build(int n)
{
    for(int i=0; i<mxM; i++) lc[i]=rc[i]=-1;
    m=1;
    while(m<n) m<<=1;
}

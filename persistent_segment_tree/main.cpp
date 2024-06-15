int lc[mxM], rc[mxM], sum[mxM], sz=1, m=1;
int upd(int l, int r, int x, int i, int Lx=0, int Rx=m)
{
    if(Rx<=l||Lx>=r) return i;
    int nw=sz++;
    if(~i) lc[nw]=lc[i], rc[nw]=rc[i], sum[nw]=sum[i];
    if(Lx>=l && Rx<=r)
    {
        sum[nw]+=x;
        return nw;
    }
    int m=(Lx+Rx)/2;
    lc[nw]=upd(l,r,x,~i?lc[i]:-1,Lx,m);
    rc[nw]=upd(l,r,x,~i?rc[i]:-1,m,Rx);
    return nw;
}
int query(int l, int r, int i, int Lx=0, int Rx=m)
{
    if(Rx<=l||Lx>=r||!~i) return 0;
    if(Lx>=l && Rx<=r) return sum[i];
    int m=(Lx+Rx)>>1;
    return query(l,r,lc[i],Lx,m)+query(l,r,rc[i],m,Rx);
}
int qry(int pos, int i, int Lx=0, int Rx=m)
{
    if(!~i) return 0;
    if(Rx-Lx==1) return sum[i];
    int m=(Lx+Rx)>>1;
    if(pos<m) return sum[i]+qry(pos,lc[i],Lx,m);
    else      return sum[i]+qry(pos,rc[i],m,Rx);
}
int upd(int pos, int x, int i, int Lx=0, int Rx=m)
{
    int nw=sz++;
    if(~i) lc[nw]=lc[i], rc[nw]=rc[i], sum[nw]=sum[i];
    sum[nw]+=x;
    if(Rx-Lx==1) return nw;
    int m=(Lx+Rx)>>1;
    if(pos<m) lc[nw]=upd(pos,x,~i?lc[i]:-1,Lx,m);
    else rc[nw]=upd(pos,x,~i?rc[i]:-1,m,Rx);
    return nw;
}

void build(int n)
{
    for(int i=0; i<mxM; i++) lc[i]=rc[i]=-1;
    m=1;
    while(m<n) m<<=1;
}

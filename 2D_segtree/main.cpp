int val[mxN][mxN];
void upd_x(int v, int l, int r, int i, int j=0, int Lx=0, int Rx=1024)
{
    if(Rx<=l || Lx>=r) return;
    if(Lx>=l && Rx<=r)
    {
        val[i][j]+=v;
        return;
    }
    int m=(Rx+Lx)/2;
    upd_x(v,l,r,i,j*2+1,Lx,m);
    upd_x(v,l,r,i,j*2+2,m,Rx);
}
void upd_y(int v, int lx, int rx, int ly, int ry, int i=0, int Lx=0, int Rx=1024)
{
    if(Rx<=ly || Lx>=ry) return;
    if(Lx>=ly && Rx<=ry)
    {
        upd_x(v,lx,rx,i);
        return;
    }
    int m=(Rx+Lx)/2;
    upd_y(v,lx,rx,ly,ry,i*2+1,Lx,m);
    upd_y(v,lx,rx,ly,ry,i*2+2,m,Rx);
}

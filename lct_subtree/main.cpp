int p[mxN], ch[mxN][2];
bool tag[mxN];
int cc[mxN], vc[mxN];
void recalc(int x)
{
    cc[x]=1+vc[x]+cc[ch[x][0]]+cc[ch[x][1]]; ///care for 0
}
int side(int x)
{
    if(ch[p[x]][0]==x) return 0;
    if(ch[p[x]][1]==x) return 1;
    return -1;
}
void flip(int x)
{
    swap(ch[x][0],ch[x][1]);
    tag[x]^=1;
}
void push(int x)
{
    if(tag[x])
    {
        flip(ch[x][0]), flip(ch[x][1]);
        tag[x]=0;
    }
}
void clear_path(int x)
{
    if(~side(x)) clear_path(p[x]);
    push(x);
}
void rotate(int x)
{
    int y=p[x], z=p[y], dx=side(x), dy=side(y), B=ch[x][dx^1];
    if(B) p[B]=y;
    if(~dy) ch[z][dy]=x;
    p[x]=z, p[y]=x;
    ch[x][dx^1]=y, ch[y][dx]=B;
    recalc(y), recalc(x);
}
void splay(int x)
{
    clear_path(x);
    while(~side(x))
    {
        int y=p[x];
        if(!~side(y)) rotate(x);
        else if(side(x)==side(y)) rotate(y), rotate(x);
        else rotate(x), rotate(x);
    }
}
void access(int x)
{
    splay(x);
    vc[x]+=cc[ch[x][1]];
    ch[x][1]=0;
    while(p[x])
    {
        int y=p[x];
        splay(y);
        vc[y]+=cc[ch[y][1]]-cc[x];
        ch[y][1]=x;
        recalc(y);
        rotate(x);
    }
}
int find_root(int x)
{
    access(x);
    while(ch[x][0]) x=ch[x][0];
    splay(x);
    return x;
}
void change_root(int x)
{
    access(x);
    flip(x);
}
void link(int x, int y)
{
    change_root(x);
    change_root(y);
    cc[y]+=cc[x];
    vc[y]+=cc[x];
    p[x]=y;
}
void cut(int x, int y)
{
    change_root(x);
    access(y);
    ch[y][0]=0;
    recalc(y);
    p[x]=0;
}
void init(int n)
{
    for(int i=1; i<=n; i++) recalc(i);
}

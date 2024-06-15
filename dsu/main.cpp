int sz[mxN], p[mxN];
int comp;
void build(int n)
{
    for(int i=0; i<n; i++) sz[i]=1, p[i]=i;
    comp=n;
}
int get(int x)
{
    if(p[x]^x) p[x]=get(p[x]);
    return p[x];
}
int unite(int a, int b)
{
    a=get(a), b=get(b);
    if(a==b) return 0;
    if(sz[a]>sz[b]) swap(a,b);
    p[a]=b;
    sz[b]+=sz[a];
    comp--;
    return 1;
}

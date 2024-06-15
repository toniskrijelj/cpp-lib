
struct treap{
    treap *left, *right;
    ll w, size, v, sum, tag;
    treap(ll v) ///reset tags
    {
        left=right=0;
        w=mt_rand();
        sum=v;
        tag=0;
        reset();
    }
    void reset() ///reset values
    {
        size=1;
    }
};
int size(treap* t)
{
    return t?t->size:0;
}
ll sum(treap* t)
{
    return t?t->sum:0;
}
void prop(treap* t)
{
    if(!t) return;
    if(t->tag)
    {
        t->tag=0;
    }
}
void recalc(treap *&t, treap* left, treap* right)
{
    if(!left||!right) return;
    t->size=left->size+right->size;
}
void recalc(treap* t)
{
    if(!t) return;
    t->reset();
    recalc(t,t->left,t);
    recalc(t,t,t->right);
}
void split(treap* t, treap* &left, treap* &right, int k)
{
    prop(t),prop(left),prop(right);
    if(!t) left=right=0;
    else
    {
        if(size(t->left) < k) split(t->right,t->right,right,k-size(t->left)-1), left=t;
        else split(t->left,left,t->left,k), right = t;
        recalc(t);
    }
}
void merge(treap* &t, treap* left, treap* right)
{
    prop(t),prop(left),prop(right);
    if(!left) t=right;
    else if(!right) t=left;
    else
    {
        if(left->w<right->w) merge(left->right,left->right,right), t=left;
        else merge(right->left,left,right->left), t=right;
        recalc(t);
    }
}
void add(treap* t, ll x)
{
    if(!t) return;
    t->sum=(t->sum+x)%mod;
    t->tag=(t->tag+x)%mod;
}
/*
void add(treap *&t, int i, ll v)
{
    prop(t);
    if(size(t->left) >= i) add(t->left, i, v);
    else if(size(t->left)+1==i) t->v += v;
    else add(t->right, i-size(t->left)-1, v);
    t->sum = sum(t->left)+sum(t->right)+t->v;
}
ll get(treap *t, int i)
{
    prop(t);
    if(size(t->left) >= i) return get(t->left, i);
    if(size(t->left)+1==i) return t->v;
    return get(t->right, i-size(t->left)-1);
}*/

/// array verzija
struct treap{
    int left, right;
    ll w, size, sum, tag;
    treap() ///reset tags
    {
        left=right=0;
        w=mt_rand();
        sum=tag=0;
        reset();
    }
    void reset() ///reset values
    {
        size=1;
    }
}ts[mxN];
void prop(int t)
{
    if(!t) return;
    if(ts[t].tag)
    {
        int L=ts[t].left, R=ts[t].right;
        if(L) ts[L].tag+=ts[t].tag, ts[L].sum+=ts[t].tag;
        if(L) ts[L].tag%=mod, ts[L].sum%=mod;
        if(R) ts[R].tag+=ts[t].tag, ts[R].sum+=ts[t].tag;
        if(R) ts[R].tag%=mod, ts[R].sum%=mod;
        ts[t].tag=0;
    }
}
void recalc(int t, int left, int right)
{
    if(!left||!right) return;
    ts[t].size=ts[left].size+ts[right].size;
}
void recalc(int t)
{
    if(!t) return;
    ts[t].reset();
    recalc(t,ts[t].left,t);
    recalc(t,t,ts[t].right);
}
void split(int t, int &left, int &right, int k)
{
    prop(t),prop(left),prop(right);
    if(!t) left=right=0;
    else
    {
        if(ts[ts[t].left].size < k) split(ts[t].right,ts[t].right,right,k-ts[ts[t].left].size-1), left=t;
        else split(ts[t].left,left,ts[t].left,k), right=t;
        recalc(t);
    }
}
void merge(int &t, int left, int right)
{
    prop(t),prop(left),prop(right);
    if(!left) t=right;
    else if(!right) t=left;
    else
    {
        if(ts[left].w<ts[right].w) merge(ts[left].right,ts[left].right,right), t=left;
        else merge(ts[right].left,left,ts[right].left), t=right;
        recalc(t);
    }
}
void add(int t, ll x)
{
    if(!t) return;
    ts[t].sum=(ts[t].sum+x)%mod;
    ts[t].tag=(ts[t].tag+x)%mod;
}
///ts[0].size=0 !!!!!!!!

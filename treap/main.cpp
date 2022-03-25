
struct treap{
    treap *left, *right;
    int w, size, v;
    ll sum;
    treap(int vv) ///reset tags
    {
        left=right=NULL;
        w = mt_rand();
        set(vv);
    }
    void set(int vv) ///reset values
    {
        v = vv;
        size = 1;
        sum = vv;
    }
};
int size(treap* t)
{
    if(!t) return 0;
    return t->size;
}
ll sum(treap* t)
{
    return t?t->sum:0;
}
void prop(treap* t)
{
    if(!t) return;
}
void recalc(treap *&t, treap* left, treap* right)
{
    if(left==NULL||right==NULL) return;
    t->size = left->size+right->size;
    t->sum = left->sum+right->sum;
}
void recalc(treap* t)
{
    if(!t) return;
    t->set(t->v);
    recalc(t, t->left, t);
    recalc(t, t, t->right);
}
void split(treap* t, treap* &left, treap* &right, int k)
{
    prop(t), prop(left), prop(right);
    if(t == NULL) left = right = NULL;
    else
    {
        if(size(t->left) < k)
        {
            split(t->right, t->right, right, k-size(t->left)-1);
            left = t;
        }
        else
        {
            split(t->left, left, t->left, k);
            right = t;
        }
        recalc(t);
    }
}
void merge(treap *&t, treap* left, treap* right)
{
    prop(t), prop(left), prop(right);
    if(left == NULL) t = right;
    else if(right == NULL) t = left;
    else
    {
        if(left->w < right->w)
        {
            merge(left->right, left->right, right);
            t = left;
        }
        else
        {
            merge(right->left, left, right->left);
            t = right;
        }
        recalc(t);
    }
}
void add(treap *&t, int index, ll v)
{
    prop(t);
    if(size(t->left) >= index) add(t->left, index, v);
    else if(size(t->left)+1==index) t->v += v;
    else add(t->right, index-size(t->left)-1, v);
    t->sum = sum(t->left)+sum(t->right)+t->v;
}
ll get(treap *t, int index)
{
    prop(t);
    if(size(t->left) >= index) return get(t->left, index);
    if(size(t->left)+1==index) return t->v;
    return get(t->right, index-size(t->left)-1);
}

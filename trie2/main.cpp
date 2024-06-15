struct trie_struct
{
    int mp[2];
    trie_struct() { clear(); }
    void clear() { mp[0]=mp[1]=-1; }
    int& operator[](const int& i) { return mp[i]; }
};
const int bits=18;
trie_struct tr[mxN*mxB];
int sz=1;
void insert(int x, int t=0)
{
    for(int i=0; i<mxB; i++)
    {
        bool b=x&(1<<(bits-1-i));
        if(!~tr[t][b]) tr[t][b]=sz++;
        t=tr[t][b];
    }
}
void reset()
{
    for(int i=0; i<sz; i++) tr[i].clear();
    sz=1;
}
int mn(int x, int t=0)
{
    int ans=0;
    for(int i=0; i<mxB; i++)
    {
        bool b=x&(1<<(mxB-1-i));
        if(~tr[t][b]) t=tr[t][b];
        else
        {
            ans+=1<<(mxB-1-i);
            t=tr[t][!b];
        }
    }
    return ans;
}
int mx(int x, int t=0)
{
    int ans=0;
    for(int i=0; i<mxB; i++)
    {
        bool b=!(x&(1<<(mxB-1-i)));
        if(~tr[t][b])
        {
            t=tr[t][b];
            ans+=1<<(bits-1-i);
        }
        else t=tr[t][!b];
    }
    return ans;
}

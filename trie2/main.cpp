struct trie_struct
{
    int mp[2];
    trie_struct()
    {
        clear();
    }
    void clear()
    {
        mp[0]=mp[1]=-1;
    }
    int& operator[](const int& i)
    {
        return mp[i];
    }
};
const int bits=17;
trie_struct tr[mxN*bits];

int a[mxN];
int sz = 1;
void insert(int x, int t = 0)
{
    for(int bit = 0; bit < bits; bit++)
    {
        bool b = x&(1<<(bits-1-bit));
        if(tr[t][b]==-1) tr[t][b] = sz++, tr[tr[t][b]].clear();
        t = tr[t][b];
    }
}
void reset()
{
    sz=1;
    tr[0].clear();
}
int mn(int x, int t = 0)
{
    int ans = 0;
    for(int bit = 0; bit < bits; bit++)
    {
        bool b = x&(1<<(bits-1-bit));
        if(tr[t][b]==-1)
        {
            ans += 1<<(bits-1-bit);
            t = tr[t][!b];
        }
    }
}
int mx(int x, int t = 0)
{
    int ans = 0;
    for(int bit = 0; bit < bits; bit++)
    {
        bool b = !(x&(1<<(bits-1-bit)));
        if(tr[t][b]==-1)
        {
            t = tr[t][!b];
        }
        else
        {
            ans += 1<<(bits-1-bit);
            t = tr[t][b];
        }
    }
    return ans;
}

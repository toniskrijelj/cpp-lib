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
trie_struct tr[mxN*31];
int a[mxN];

int sz = 1;
void add(int x, int t = 0)
{
    for(int bit = 0; bit < 30; bit++)
    {
        bool b = x&(1<<(30-1-bit));
        if(tr[t][b]==-1) tr[t][b] = sz++;
        t = tr[t][b];
    }
}
int find(int x, int t = 0)
{
    ll ans = 0;
    for(int bit = 0; bit < 30; bit++)
    {
        bool b = x&(1<<(30-1-bit));
        if(tr[t][b]!=-1) t = tr[t][b];
        else
        {
            ans += 1<<(30-1-bit);
            t = tr[t][!b];
        }
    }
    return ans;
}

struct struct_trie
{
    int mp[2];
    bool en;
    int& operator[](const int& i)
    {
        return mp[i];
    }
    struct_trie()
    {
        mp[0]=mp[1]=-1;
        en=0;
    }
};
struct_trie tr[mxN*mxK];
int sz=1;
void insert(int x)
{
    int t=0;
    vector<int> vis;
    for(int bit=mxK-1; bit>=0; bit--)
    {
        bool b=x&(1<<bit);
        if(!~tr[t][b]) tr[t][b]=sz++;
        vis.push_back(t);
        t=tr[t][b];
    }
    tr[t].en = 1;
    while(vis.size())
    {
        t=vis.back(); vis.pop_back();
        tr[t].complete=~tr[t][0]&&~tr[t][1]&&tr[tr[t][0]].en&&tr[tr[t][1]].en;
    }
}
int find(int x)
{
    int t=0, ans=0, t2;
    for(int bit=mxK-1; bit>=0; bit--)
    {
        if(!~t) break;
        bool flip=x&(1<<bit);
        if(flip) swap(tr[t][0], tr[t][1]);
        if(tr[t][0]==-1 || !tr[tr[t][0]].complete) t2 = tr[t][0];
        else
        {
            t2 = tr[t][1];
            ans += 1<<bit;
        }
        if(flip) swap(tr[t][0], tr[t][1]);
        t = t2;
    }
    return ans;
}

struct _trie
{
    int mp[2], cnt;
    int& operator[](const int& i) { return mp[i]; }
    _trie() { mp[0]=mp[1]=-1; cnt=0; }
};
_trie tr[mxN*K];
int sz=2;
void insert(int t, int x, int s)
{
    tr[t].cnt+=s;
    for(int bit=K-1; bit>=0; bit--)
    {
        int b=x>>bit&1;
        if(!~tr[t][b]) tr[t][b]=sz++;
        t=tr[t][b];
        tr[t].cnt+=s;
    }
}
int find(int t, int x)
{
    for(int bit=K-1; bit>=0; bit--)
    {
        int b=x>>bit&1;
        if(~tr[t][!b]&&tr[tr[t][!b]].cnt) t=tr[t][!b], x^=!b<<bit;
        else if(~tr[t][b]&&tr[tr[t][b]].cnt) t=tr[t][b], x^=b<<bit;
        else return 0;
    }
    return x;
}

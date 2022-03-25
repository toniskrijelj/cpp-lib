struct struct_trie
{
    int mp[2];
    bool complete;
    int xr;
    int& operator[](const int& i)
    {
        return mp[i];
    }
    struct_trie()
    {
        mp[0]=mp[1]=-1;
        complete = 0;
    }
};
struct_trie tr[mxN*mxK];
int sz = 1;
void insert(int x)
{
    int t = 0;
    vector<int> vis;
    for(int bit = mxK-1; bit >= 0; bit--)
    {
        bool b = x&(1<<bit);
        if(tr[t][b]==-1) tr[t][b]=sz++;
        vis.push_back(t);
        t = tr[t][b];
    }
    tr[t].complete = 1;
    while(vis.size())
    {
        t = vis.back(); vis.pop_back();
        tr[t].complete =
            tr[t][0]!=-1&&
            tr[t][1]!=-1&&
            tr[tr[t][0]].complete&&
            tr[tr[t][1]].complete;
    }
}
int find(int x)
{
    int t = 0, ans = 0, t2;
    for(int bit = mxK-1; bit >= 0; bit--)
    {
        if(t==-1) break;
        bool flip = x&(1<<bit);
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

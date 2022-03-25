struct DSU
{
    vector<int> size, p;
    int comp;
    void build(int n)
    {
        size = vector<int>(n, 1);
        p = vector<int>(n);
        iota(p.begin(), p.end(), 0);
        comp = n;
    }
    int get(int x)
    {
        if(p[x] != x) p[x] = get(p[x]);
        return p[x];
    }
    bool unite(int a, int b)
    {
        a = get(a), b = get(b);
        if(a == b) return 0;
        if(size[a] > size[b]) swap(a, b);
        p[a] = b;
        size[b] += size[a];
        comp--;
        return 1;
    }
};

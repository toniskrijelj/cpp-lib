void dfs2(int i)
{
    while(adj[i].size())
    {
        auto edge = adj[i].back();
        adj[i].pop_back();
        int j = edge.first, k = edge.second;
        if(ok[k]) continue;
        ok[k] = 1;
        dfs2(j);
        cout << i << " ";
    }
}
//one cc, all even or path from 2 odds

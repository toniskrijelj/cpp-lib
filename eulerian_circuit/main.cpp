vector<pair<int,int>> adj[mxN];
vector<int> ord;
int ok[mxN];
void dfs(int i)
{
    while(adj[i].size())
    {
        auto [j,e]=adj[i].back(); adj[i].pop_back();
        if(ok[e]) continue;
        ok[e]=1;
        dfs(j);
    }
    ord.push_back(i);
}
//one cc, all even or path from 2 odds

vector<pair<int,int>> adj[mxN];
vector<int> ord;
int done[mxN];
void dfs(int i)
{
    while(adj[i].size())
    {
        auto [j,e]=adj[i].back(); adj[i].pop_back();
        if(done[e]) continue;
        done[e]=1;
        dfs(j);
    }
    ord.push_back(i);
}
//one cc, all even or path from 2 odds

void dfs(int i, int e=-1)
{
    while(adj[i].size())
    {
        auto [j,e]=adj[i].back(); adj[i].pop_back(); //ako trebaju edgevi
        if(done[e]) continue;
        done[e]=1;
        dfs(j,e);
    }
    if(~e) ord.push_back(e);
}
///https://codeforces.com/contest/2110/submission/321153391

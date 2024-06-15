//const ll inf = 1e18;
const int N = 1202;
const int ADD = 600;
struct edge
{
    int a, b; ll cap; int rev;
};
edge es[mxN];
int sz, p[mxN];
vector<int> adj[mxN];
bool vis[mxN];
void add(int a, int b, int cap)
{
    es[sz]  ={a,b,cap,sz+1};
    es[sz+1]={b,a,0,  sz, };
    adj[a].push_back(sz);
    adj[b].push_back(sz+1);
    sz+=2;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll mf=0;
    while(1)
    {
        for(int i=0; i<N; i++) vis[i]=0;
        vis[0]=1;
        queue<int> q; q.push(0);
        while(q.size())
        {
            int u=q.front(); q.pop();
            for(int e:adj[u])
            {
                int v=es[e].b;
                if(es[e].cap&&!vis[v])
                {
                    q.push(v);
                    p[v]=e;
                    vis[v]=1;
                }
            }
        }
        if(!vis[N-1]) break;
        ll f=K-mf; ///ogranicen K
        int u=N-1;
        while(u)
        {
            f=min(f,es[p[u]].cap);
            u=es[p[u]].a;
        }
        u=N-1;
        while(u)
        {
            es[p[u]].cap-=f;
            es[es[p[u]].rev].cap+=f;
            u=es[p[u]].a;
        }
        mf+=f;
        if(mf==K) break; ///ogranicen K
    }

    for(int e=0; e<sz; e+=2) ///maximum indepedent set / minimum node cover
    {
        if(es[e].a>0&&es[e].b<N-1)
        {
            if(!es[e].cap)
            {
                adj2[es[e].b].push_back(es[e].a);
                mt[es[e].a]=1;
            }
            else adj2[es[e].a].push_back(es[e].b);
        }
    }
    for(int i=1; i<=n; i++) if(!mt[i]) dfs2(i);
    vector<pair<int,int>> ans;
    for(int i=1; i<=n; i++) if(!vis2[i]) ans.push_back(i);
    for(int i=1; i<=n; i++) if(vis2[i+n]) ans.push_back(i+n); ///minimum node cover
}

/**
2 5 12 13 14 15
*/

struct mcmf
{
    struct edge
    {
        int a, b; ll cap; int rev; ll cost;
    };
    int sz,N;
    vector<edge> es;
    vector<int> p, vis;
    vector<vector<int>> adj;
    vector<ll> d, pi;
    mcmf(int n)
    {
        N=n;
        sz=0, N=n;
        p=vector<int>(n), vis=vector<int>(n);
        adj=vector<vector<int>>(n);
        d=vector<ll>(n), pi=vector<ll>(n);
    }
    void add_edge(int a, int b, int cap, ll cost)
    {
        es.push_back({a,b,cap,sz+1,cost});
        es.push_back({b,a,0,  sz, -cost});
        adj[a].push_back(sz);
        adj[b].push_back(sz+1);
        sz+=2;
    }
    pair<ll,ll> max_flow()
    {
        for(int i=0; i<N; i++) pi[i]=d[i]=inf, p[i]=-1;
        pi[0]=0;
        for(int i=0; i<N; i++)
        for(int j=0; j<sz; j++)
        if(es[j].cap&&pi[es[j].a]+es[j].cost<pi[es[j].b])
        pi[es[j].b]=pi[es[j].a]+es[j].cost;
        ll cost=0, mf=0;
        while(1)
        {
            d[0]=0;
            priority_queue<pair<ll, int>> pq;
            pq.push({0,0});
            while(!pq.empty())
            {
                auto cur=pq.top(); pq.pop();
                int u=cur.second;
                if(vis[u]) continue;
                vis[u]=1;
                for(int j:adj[u])
                {
                    int v=es[j].b;
                    ll w=es[j].cost+pi[u]-pi[v];
                    if(es[j].cap&&w+d[u]<d[v])
                    {
                        p[v]=j;
                        d[v]=w+d[u];
                        pq.push({-d[v],v});
                    }
                }
            }
            if(!~p[N-1]) break;
            int u=N-1;
            ll f=inf;
            while(u)
            {
                int j=p[u];
                f=min(f,es[j].cap);
                u=es[j].a;
            }
            u=N-1;
            while(u)
            {
                int j=p[u];
                es[j].cap-=f;
                es[es[j].rev].cap+=f;
                u=es[j].a;
            }
            cost+=(d[N-1]+pi[N-1]-pi[0])*f;
            mf+=f;
            for(int i=0; i<N; i++) pi[i]+=d[i], d[i]=inf, p[i]=-1, vis[i]=0;
        }
        return {mf,cost};
    }
};


//const ll inf = 1e18;
const int N = 302;
const int ADD = 150;
struct edge
{
    int a, b; ll cap; int rev; ll cost;
};
edge es[mxN];
int sz, p[mxN];
vector<int> adj[mxN];
ll d[mxN], pi[mxN];
bool vis[mxN];
void add(int a, int b, int cap, ll cost)
{
    es[sz]  ={a,b,cap,sz+1,cost};
    es[sz+1]={b,a,0,  sz, -cost};
    adj[a].push_back(sz);
    adj[b].push_back(sz+1);
    sz+=2;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for(int i=0; i<N; i++) pi[i]=d[i]=inf, p[i]=-1;
    pi[0]=0;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<sz; j++)
        {
            if(es[j].cap&&pi[es[j].a]+es[j].cost<pi[es[j].b])
            {
                pi[es[j].b]=pi[es[j].a]+es[j].cost;
            }
        }
    }
    ll cost=0, mf=0;
    while(1)
    {
        d[0]=0;
        priority_queue<pair<ll, int>> pq;
        pq.push({0,0});
        while(!pq.empty())
        {
            auto cur=pq.top(); pq.pop();
            int u=cur.second;
            if(vis[u]) continue;
            vis[u]=1;
            for(int j:adj[u])
            {
                int v=es[j].b;
                ll w=es[j].cost+pi[u]-pi[v];
                if(es[j].cap&&w+d[u]<d[v])
                {
                    p[v]=j;
                    d[v]=w+d[u];
                    pq.push({-d[v],v});
                }
            }
        }
        if(!~p[N-1]) break;
        int u=N-1;
        ll f=inf; ///k-mf
        while(u)
        {
            int j=p[u];
            f=min(f,es[j].cap);
            u=es[j].a;
        }
        u=N-1;
        while(u)
        {
            int j=p[u];
            es[j].cap-=f;
            es[es[j].rev].cap+=f;
            u=es[j].a;
        }
        cost+=(d[N-1]+pi[N-1]-pi[0])*f;
        mf+=f;
        ///if max flow achieved break
        for(int i=0; i<N; i++) pi[i]+=d[i], d[i]=inf, p[i]=-1, vis[i]=0;
    }
}

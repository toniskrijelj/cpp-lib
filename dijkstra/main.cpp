priority_queue<pair<ll, int>> pq;
pq.push({0,x});
while(pq.size())
{
    auto par=pq.top(); pq.pop();
    int i=par.second;
    if(vis[i]) continue;
    vis[i]=1;
    for(int e:out[i])
    {
        int j=es[e].v;
        ll w=es[e].w;
        if(to[i]+w<to[j])
        {
            to[j]=to[i]+w;
            pq.push({-to[j],j});
        }
    }
}

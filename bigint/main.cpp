void multiply(vector<int> &x, ll y)
{
    for(ll i=0, c=0; i<(int)x.size() || c; i++)
    {
        if(i==(int)x.size()) x.push_back(0);
        ll cur=x[i]*y+c;
        c=cur/10;
        x[i]=cur%10;
    }
    while(x.size() && !x.back()) x.pop_back();
}
vector<int> powb(int y)
{
    vector<int> x={1};
    for(int i=0; i<y; i++) multiply(x,5);
    return x;
}
void divide(vector<int> &x, ll y)
{
    for(ll i=(int)x.size()-1, r=0; i>=0; i--)
    {
        ll cur=x[i]+r*10;
        x[i]=cur/y;
        r=cur%y;
    }
    while(x.size() && !x.back()) x.pop_back();
}
void print(vector<int> &x)
{
    for(int i=(int)x.size()-1; i>=0; i--) cout << x[i];
    cout << "\n";
}

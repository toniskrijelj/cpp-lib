//https://codeforces.com/contest/1856/problem/E2
template<int len=1>
void solve(int n)
{
    if(n>=len)
    {
        solve<min(len<<1,1<<20)>(n);
        return;
    }
    bitset<len> dp;
}

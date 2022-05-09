///https://codeforces.com/contest/985/submission/137594760
ll powb(ll a, ll x, const ll MOD)
{
    ll ret=1;
    a%=MOD;
    while(x)
    {
        if(x&1)ret=ret*a%MOD;
        x>>=1;
        a=a*a%MOD;
    }
    return ret;
}
ll inv(ll a, const ll MOD)
{
    return powb(a, MOD-2, MOD);
}
const int HASH_SIZE = 2;
const ll hshmod[HASH_SIZE] = {(ll)1e9+7, (ll)1e9+9};
const ll hshbase[HASH_SIZE] = {31, 29};
ll basepow[HASH_SIZE][mxN];
ll baseinv[HASH_SIZE][mxN];
ll hsh[HASH_SIZE][mxK][mxN];
void precalc()
{
    for(int i = 0; i < HASH_SIZE; i++)
    {
        basepow[i][0] = baseinv[i][0] = 1;
    }
    for(int j = 0; j < HASH_SIZE; j++)
    {
        for(int i = 1; i < mxN; i++)
        {
            basepow[j][i] = basepow[j][i-1]*hshbase[j]%hshmod[j];
            baseinv[j][i] = inv(basepow[j][i], hshmod[j]);
        }
    }

}
ll calc_hsh(int base, int j, int l, int r) ///base 1 indexing
{
    return (hsh[base][j][r]-hsh[base][j][l-1]+hshmod[base])%hshmod[base]
            *baseinv[base][l-1]%hshmod[base]; ///shift to left
}
void do_hash(int j, string& s) ///delete J if  doesnt exist
{
    int n = s.size();
    for(int base = 0; base < HASH_SIZE; base++)
    {
        for(int i = 1; i <= n; i++)
        {
            hsh[base][j][i]=(hsh[base][j][i-1]+(s[i-1]-'a'+1)*basepow[base][i-1])%hshmod[base];
        }
    }
}
void do_hash(int j, string& s) ///1 base indexing
{
    int n = s.size();
    for(int base = 0; base < HASH_SIZE; base++)
    {
        for(int i = 1; i <= n; i++)
        {
            hsh[base][j][i]=(hsh[base][j][i-1]+(s[i-1]-'A'+1)*basepow[base][i-1])%hshmod[base];
            //cout << hsh[base][j][i] << " ";
        }
        //cout << "\n";
    }
}

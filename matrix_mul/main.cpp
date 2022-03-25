void mul(vector<vector<ll>>& A, vector<vector<ll>>& B, int n)
{
    vector<vector<ll>> C(n, vector<ll>(n, 0));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            for(int k = 0; k < n; k++)
            {
                C[i][k] = (C[i][k]+A[i][j]*B[j][k]%mod)%mod;
            }
        }
    }
    for(int j = 0; j <= n; j++)
    {
        for(int i = 0; i <= n; i++)
        {
            A[j][i] = C[j][i];
        }
    }
}
void powb(vector<vector<ll>>& mat, int n, int k)
{
    ///[0,n)
    vector<vector<ll>> mat2(n, vector<ll>(n, 0));
    for(int j = 0; j < n; j++)
    {
        for(int i = 0; i < n; i++)
        {
            if(i==j) mat2[j][i] = 1;
        }
    }
    while(k)
    {
        if(k&1)
        {
            mul(mat2, mat, n);
        }
        k>>=1;
        mul(mat, mat, n);
    }
    for(int j = 0; j < n; j++)
    {
        for(int i = 0; i < n; i++)
        {
            mat[j][i] = mat2[j][i];
        }
    }
}

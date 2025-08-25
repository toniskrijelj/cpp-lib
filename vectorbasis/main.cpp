const int K=30;
int bs[K], bs2[K];
int sz;
void insert(int x)
{
    int y=x;
    for(int i=0; i<K; i++)
    {
        if(!(x>>i&1)) continue;
        if(!bs[i])
        {
            sz++;
            bs[i]=x;
            bs2[i]=y;
            return;
        }
        x^=bs[i];
    }
}
///gray code i^(i>>1)

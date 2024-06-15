const int MAX_BITS=30;
int basis[MAX_BITS], basis2[MAX_BITS];
int sz;
void insert(int x)
{
    int y=x;
    for(int i=0; i<MAX_BITS; i++)
    {
        if(!(x&(1<<i))) continue;
        if(!basis[i])
        {
            sz++;
            basis[i]=x;
            basis2[i]=y;
            return;
        }
        x^=basis[i];
    }
}
///gray code i^(i>>1)

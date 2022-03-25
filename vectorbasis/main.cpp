int basis[30];
int sz;
void insert(int x)
{
    for(int i = 0; i < 30; i++)
    {
        if(!(x&(1<<i))) continue;
        if(!basis[i])
        {
            sz++;
            basis[i] = x;
            return;
        }
        x ^= basis[i];
    }
}

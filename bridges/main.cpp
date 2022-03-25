#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int mxN = 2005;
const int mxK = 26;


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while(t--)
    {
        int a, b; cin >> a >> b;
        if((a+b)%3 == 0 && min(a,b)*2 >= max(a,b)) cout << "YES\n";
        else cout << "NO\n";
    }
}

//74 74 74


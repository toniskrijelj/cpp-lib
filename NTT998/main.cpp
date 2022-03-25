using pii = pair<int, int>;
using cd = complex<ld>;

template<int MOD>
struct modInt
{
    int x;

    void normalize()
    {
        if (x < 0) x += MOD;
        else if (x >= MOD) x -= MOD;
    }

    modInt() = default;

    modInt(int x) : x(x)
    {
        normalize();
    }

    modInt(ll x) : x(int(x % MOD))
    {
        normalize();
    }

    friend modInt operator+(const modInt &a, const modInt &b)
    {
        return modInt(a.x + b.x);
    }

    friend modInt operator-(const modInt &a, const modInt &b)
    {
        return modInt(a.x - b.x);
    }

    friend modInt operator*(const modInt &a, const modInt &b)
    {
        return modInt((ll) a.x * b.x);
    }

    friend modInt operator/(modInt a, modInt b)
    {
        int p = MOD - 2;
        while (p > 0)
        {
            if (p % 2)
            {
                a = a * b;
            }
            b = b * b;
            p /= 2;
        }
        return a;
    }

    modInt &operator+=(const modInt &b)
    {
        return *this = *this + b;
    }

    modInt &operator-=(const modInt &b)
    {
        return *this = *this - b;
    }

    modInt &operator*=(const modInt &b)
    {
        return *this = *this * b;
    }

    modInt &operator/=(const modInt &b)
    {
        return *this = *this / b;
    }

    bool operator<(const modInt &other) const
    {
        return x < other.x;
    }

    bool operator>(const modInt &other) const
    {
        return x > other.x;
    }

    bool operator<=(const modInt &other) const
    {
        return x <= other.x;
    }

    bool operator>=(const modInt &other) const
    {
        return x >= other.x;
    }

    bool operator==(const modInt &other) const
    {
        return x == other.x;
    }

    bool operator!=(const modInt &other) const
    {
        return x != other.x;
    }
};

template<int MOD>
ostream &operator<<(ostream &out, modInt<MOD> const &x)
{
    out << x.x;
    return out;
}

template<int MOD>
istream &operator>>(istream &in, modInt<MOD> &x)
{
    x = 0;
    int c;
    while (isdigit(c = in.get()))
    {
        x *= 10;
        x += c - '0';
    }
    return in;
}

using mint = modInt<998'244'353>;

const int LOG = 20;
const int N = 1 << LOG;

int inv[N];
mint w[N];
mint g;
mint invN[LOG];
mint fact[N];
mint invFact[N];

void init()
{
    for (g = 2;; g += 1)
    {
        mint x = g;
        for (int i = 0; i < LOG - 1; i++)
        {
            x *= x;
        }
        if (x == -1)
        {
            break;
        }
    }
    w[0] = 1;
    for (int i = 1; i < N; i++)
    {
        w[i] = w[i - 1] * g;
    }
    for (int i = 1; i < N; i++)
    {
        inv[i] = (inv[i >> 1] >> 1) | ((i & 1) << (LOG - 1));
    }
    for (int i = 0; i < LOG; i++)
    {
        invN[i] = mint(1) / (1 << i);
    }

    fact[0] = fact[1] = 1;
    for (int i = 2; i < N; i++)
    {
        fact[i] = fact[i - 1] * i;
    }
    invFact[N - 1] = mint(1) / fact[N - 1];
    for (int i = N - 2; i >= 0; i--)
    {
        invFact[i] = invFact[i + 1] * (i + 1);
    }
}

void fft(vector<mint> &a)
{
    int n = (int) a.size();
    int log_2 = __builtin_ctz(n);
    for (int i = 0; i < n; i++)
    {
        int j = inv[i] >> (LOG - log_2);
        if (i < j)
        {
            swap(a[i], a[j]);
        }
    }
    for (int lvl = 0; lvl < log_2; lvl++)
    {
        int len = 1 << lvl;
        for (int i = 0; i < n; i += 2 * len)
        {
            for (int j = 0; j < len; j++)
            {
                mint x = a[i + j], y = a[i + j + len] * w[j << (LOG - lvl - 1)];
                a[i + j] = x + y;
                a[i + j + len] = x - y;
            }
        }
    }
}

void mult(vector<mint> &a, const vector<mint> &b)
{
    int n = 1;
    while (n < (int)a.size() + (int)b.size())
    {
        n *= 2;
    }
    int log_2 = __builtin_ctz(n);
    static vector<mint> A, B;
    A.resize(n);
    B.resize(n);
    fill(A.begin(), A.end(), 0);
    fill(B.begin(), B.end(), 0);
    copy(a.begin(), a.end(), A.begin());
    copy(b.begin(), b.end(), B.begin());
    fft(A);
    fft(B);
    for (int i = 0; i < n; i++)
    {
        A[i] *= B[i];
    }
    fft(A);
    reverse(A.begin() + 1, A.end());
    mint n1 = invN[log_2];
    a.resize(n);
    for (int i = 0; i < n; i++)
    {
        a[i] = A[i] * n1;
    }
    while (!a.empty() && a.back() == 0)
    {
        a.pop_back();
    }
}
init();

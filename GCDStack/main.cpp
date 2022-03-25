struct gcdstack
{
    static ll GCD(ll a, ll b)
    {
        if(b == 0) return a;
        return GCD(b, a%b);
    }
    struct elem { ll x, gcd; };
    struct _stack
    {
        stack<elem> val;
        void push(ll x)
        {
            if(val.empty()) val.push({x,x});
            else val.push({x, GCD(x, val.top().gcd)});
        }
        void pop() { val.pop(); }
        elem top() { return val.top(); }
        int size() { return val.size(); }
        bool empty() { return size()==0; }
    };
    _stack s1;
    _stack s2;
    ll calc()
    {
        if(s1.empty() && s2.empty()) return 0;
        if(s1.empty()) return s2.top().gcd;
        if(s2.empty()) return s1.top().gcd;
        return GCD(s1.top().gcd, s2.top().gcd);
    }
    void push(ll x)
    {
        s2.push(x);
    }
    void pop()
    {
        if(s1.empty()) ///pop;
        {
            while(!s2.empty())
            {
                s1.push(s2.top().x);
                s2.pop();
            }
        }
        if(!s1.empty()) s1.pop();
    }
};

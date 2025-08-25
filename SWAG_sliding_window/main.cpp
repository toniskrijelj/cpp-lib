//https://codeforces.com/contest/2004/submission/276984347
struct S
{
    int mat[10][10];
};
S op(S l, S r)
{
    S a;
    for(int i=0; i<10; i++)
    for(int j=0; j<10; j++)
    a.mat[i][j]=iinf;
    for(int i=0; i<10; i++)
    for(int j=0; j<10; j++)
    if(l.mat[i][j]<iinf)
    for(int k=0; k<10; k++)
    a.mat[i][k]=min(a.mat[i][k],l.mat[i][j]+r.mat[j][k]);
    return a;
}
S e()
{
    S a;
    for(int i=0; i<10; i++)
    for(int j=0; j<10; j++)
    if(i^j) a.mat[i][j]=iinf;
    else a.mat[i][j]=0;
    return a;
}
template <class S, S (*op)(S, S), S (*e)()> struct SWAG {
  public:
    SWAG(){
      L=stack<S>();
      R=stack<S>();
      top=e();
    }
    void push(S x){
      if(R.empty()) top=x;
      else top=op(top,x);
      R.push(x);
    }
    void pop(){
      if(L.empty()){
        while(!R.empty()){
          if(L.empty()) L.push(R.top());
          else L.push(op(R.top(),L.top()));
          R.pop();
        }
        top=e();
      }
      L.pop();
    }
    S get(){
      if(L.empty()) return top;
      return op(L.top(),top);
    }
  private:
    stack<S> L,R;
    S top;
};

using stk=SWAG<S,op,e>;


const int P = 2000 + 5;

struct item{
	int p, t;
};

const int P = 2000 + 5;

struct item{
	int p, t;
};

struct minstack {
	stack<item> st;
	stack<array<int,P>> dp;
	int get(int p) {return dp.empty() ? 0 : dp.top()[p];}
	bool empty() {return st.empty();}
	int size() {return st.size();}
	void push(item it) {
		if(empty()) dp.push(array<int,P>());
		else dp.push(dp.top());
		st.push(it);
		for(int i=P-it.p-1; i>=0; i--) dp.top()[i+it.p]=max(dp.top()[i+it.p],dp.top()[i]+it.t);
	}
	void pop() {
		st.pop();
		dp.pop();
	}
	item top() {
		return st.top();
	}
	void swap(minstack &x) {
		st.swap(x.st);
		dp.swap(x.dp);
	}
};

struct mindeque {
	minstack l, r, t;
	void rebalance() {
		int f=0;
		if(r.empty()) {f=1; l.swap(r);}
		int sz=r.size()/2;
		while(sz--) {t.push(r.top()); r.pop();}
		while(!r.empty()) {l.push(r.top()); r.pop();}
		while(!t.empty()) {r.push(t.top()); t.pop();}
		if(f) l.swap(r);
	}
	int get(int p) {
		int ans=0;
		for (int i=0; i<=p; i++) ans=max(ans, l.get(i)+r.get(p-i));
		return ans;
	}
	bool empty() {return l.empty() && r.empty();}
	int size() {return l.size() + r.size();}
	void push_front(item it) {l.push(it);}
	void push_back(item it) {r.push(it);}
	void pop_front() {if (l.empty()) rebalance(); l.pop();}
	void pop_back() {if (r.empty()) rebalance(); r.pop();}
	item front() {if (l.empty()) rebalance(); return l.top();}
	item back() {if (r.empty()) rebalance(); return r.top();}
	void swap(mindeque &x) {l.swap(x.l); r.swap(x.r);}
};

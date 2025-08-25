struct segmentTreeBeats {
private:
    static const ll INF = 1e17;

    struct Node {
        ll min, max, secondMin, secondMax, pushSum, pushEq, sum;
        int minCnt, maxCnt;
    };

    vector<Node> tree;
    int n;

    void doPushEq(int v, int l, int r, long long val) {
        tree[v].min = tree[v].max = tree[v].pushEq = val;
        tree[v].minCnt = tree[v].maxCnt = r - l;
        tree[v].secondMax = -INF;
        tree[v].secondMin = INF;

        tree[v].sum = val * (r - l);
        tree[v].pushSum = 0;
    }

    void doPushMinEq(int v, int l, int r, long long val) {
        if (tree[v].min >= val) {
            doPushEq(v, l, r, val);
        } else if (tree[v].max > val) {
            if (tree[v].secondMin == tree[v].max) {
                tree[v].secondMin = val;
            }
            tree[v].sum -= (tree[v].max - val) * tree[v].maxCnt;
            tree[v].max = val;
        }
    }

    void doPushMaxEq(int v, int l, int r, long long val) {
        if (tree[v].max <= val) {
            doPushEq(v, l, r, val);
        } else if (tree[v].min < val) {
            if (tree[v].secondMax == tree[v].min) {
                tree[v].secondMax = val;
            }
            tree[v].sum += (val - tree[v].min) * tree[v].minCnt;
            tree[v].min = val;
        }
    }

    void doPushSum(int v, int l, int r, ll val) {
        if (tree[v].min == tree[v].max) {
            doPushEq(v, l, r, tree[v].min + val);
        } else {
            tree[v].max += val;
            if (tree[v].secondMax != -INF) {
                tree[v].secondMax += val;
            }

            tree[v].min += val;
            if (tree[v].secondMin != INF) {
                tree[v].secondMin += val;
            }

            tree[v].sum += (r - l) * val;
            tree[v].pushSum += val;
        }
    }

    void pushToChildren(int v, int l, int r) {
        if (l + 1 == r) {
            return;
        }
        int mid = (r + l) / 2;
        if (tree[v].pushEq != -1) {
            doPushEq(2 * v, l, mid, tree[v].pushEq);
            doPushEq(2 * v + 1, mid, r, tree[v].pushEq);
            tree[v].pushEq = -1;
        } else {
            doPushSum(2 * v, l, mid, tree[v].pushSum);
            doPushSum(2 * v + 1, mid, r, tree[v].pushSum);
            tree[v].pushSum = 0;

            doPushMinEq(2 * v, l, mid, tree[v].max);
            doPushMinEq(2 * v + 1, mid, r, tree[v].max);

            doPushMaxEq(2 * v, l, mid, tree[v].min);
            doPushMaxEq(2 * v + 1, mid, r, tree[v].min);
        }
    }

    void updateFromChildren(int v) {
        tree[v].sum = tree[2 * v].sum + tree[2 * v + 1].sum;

        tree[v].max = max(tree[2 * v].max, tree[2 * v + 1].max);
        tree[v].secondMax = max(tree[2 * v].secondMax, tree[2 * v + 1].secondMax);
        tree[v].maxCnt = 0;
        if (tree[2 * v].max == tree[v].max) {
            tree[v].maxCnt += tree[2 * v].maxCnt;
        } else {
            tree[v].secondMax = max(tree[v].secondMax, tree[2 * v].max);
        }
        if (tree[2 * v + 1].max == tree[v].max) {
            tree[v].maxCnt += tree[2 * v + 1].maxCnt;
        } else {
            tree[v].secondMax = max(tree[v].secondMax, tree[2 * v + 1].max);
        }

        tree[v].min = min(tree[2 * v].min, tree[2 * v + 1].min);
        tree[v].secondMin = min(tree[2 * v].secondMin, tree[2 * v + 1].secondMin);
        tree[v].minCnt = 0;
        if (tree[2 * v].min == tree[v].min) {
            tree[v].minCnt += tree[2 * v].minCnt;
        } else {
            tree[v].secondMin = min(tree[v].secondMin, tree[2 * v].min);
        }
        if (tree[2 * v + 1].min == tree[v].min) {
            tree[v].minCnt += tree[2 * v + 1].minCnt;
        } else {
            tree[v].secondMin = min(tree[v].secondMin, tree[2 * v + 1].min);
        }
    }

    void build(int v, int l, int r, const vector<ll>& arr) {
        tree[v].pushSum = 0;
        tree[v].pushEq = -1;
        if (l + 1 == r) {
            tree[v].max = arr[l];
            tree[v].secondMax = -INF;
            tree[v].maxCnt = 1;

            tree[v].min = arr[l];
            tree[v].secondMin = INF;
            tree[v].minCnt = 1;

            tree[v].sum = arr[l];
        } else {
            int mid = (r + l) / 2;
            build(2 * v, l, mid, arr);
            build(2 * v + 1, mid, r, arr);
            updateFromChildren(v);
        }
    }

    void updateMinEq(int v, int l, int r, int ql, int qr, ll val) {
        if (qr <= l || r <= ql || tree[v].max <= val) {
            return;
        }
        if (ql <= l && r <= qr && tree[v].secondMax < val) {
            doPushMinEq(v, l, r, val);
            return;
        }
        pushToChildren(v, l, r);
        int mid = (r + l) / 2;
        updateMinEq(2 * v, l, mid, ql, qr, val);
        updateMinEq(2 * v + 1, mid, r, ql, qr, val);
        updateFromChildren(v);
    }

    void updateMaxEq(int v, int l, int r, int ql, int qr, ll val) {
        if (qr <= l || r <= ql || tree[v].min >= val) {
            return;
        }
        if (ql <= l && r <= qr && tree[v].secondMin > val) {
            doPushMaxEq(v, l, r, val);
            return;
        }
        pushToChildren(v, l, r);
        int mid = (r + l) / 2;
        updateMaxEq(2 * v, l, mid, ql, qr, val);
        updateMaxEq(2 * v + 1, mid, r, ql, qr, val);
        updateFromChildren(v);
    }

    void updateEq(int v, int l, int r, int ql, int qr, ll val) {
        if (qr <= l || r <= ql) {
            return;
        }
        if (ql <= l && r <= qr) {
            doPushEq(v, l, r, val);
            return;
        }
        pushToChildren(v, l, r);
        int mid = (r + l) / 2;
        updateEq(2 * v, l, mid, ql, qr, val);
        updateEq(2 * v + 1, mid, r, ql, qr, val);
        updateFromChildren(v);
    }

    void updatePlusEq(int v, int l, int r, int ql, int qr, ll val) {
        if (qr <= l || r <= ql) {
            return;
        }
        if (ql <= l && r <= qr) {
            doPushSum(v, l, r, val);
            return;
        }
        pushToChildren(v, l, r);
        int mid = (r + l) / 2;
        updatePlusEq(2 * v, l, mid, ql, qr, val);
        updatePlusEq(2 * v + 1, mid, r, ql, qr, val);
        updateFromChildren(v);
    }

    ll findSum(int v, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return tree[v].sum;
        }
        pushToChildren(v, l, r);
        int mid = (r + l) / 2;
        return findSum(2 * v, l, mid, ql, qr) + findSum(2 * v + 1, mid, r, ql, qr);
    }

    ll findMin(int v, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) {
            return INF;
        }
        if (ql <= l && r <= qr) {
            return tree[v].min;
        }
        pushToChildren(v, l, r);
        int mid = (r + l) / 2;
        return min(findMin(2 * v, l, mid, ql, qr), findMin(2 * v + 1, mid, r, ql, qr));
    }

    ll findMax(int v, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) {
            return -INF;
        }
        if (ql <= l && r <= qr) {
            return tree[v].max;
        }
        pushToChildren(v, l, r);
        int mid = (r + l) / 2;
        return max(findMax(2 * v, l, mid, ql, qr), findMax(2 * v + 1, mid, r, ql, qr));
    }

public:
    ll qry_mx(int ql, int qr) {
        return findMax(1, 0, n, ql, qr);
    }
    ll qry_mn(int ql, int qr) {
        return findMin(1, 0, n, ql, qr);
    }
    ll qry_sum(int ql, int qr) {
        return findSum(1, 0, n, ql, qr);
    }
    void upd_plus_eq(int ql, int qr, ll val) {
        updatePlusEq(1, 0, n, ql, qr, val);
    }
    void upd_eq(int ql, int qr, ll val) {
        updateEq(1, 0, n, ql, qr, val);
    }
    void upd_max_eq(int ql, int qr, ll val) {
        updateMaxEq(1, 0, n, ql, qr, val);
    }
    void upd_min_eq(int ql, int qr, ll val) {
        updateMinEq(1, 0, n, ql, qr, val);
    }
    void build(int N) {
        n=1;
        while(n<N) n<<=1;
        tree=vector<Node>(n*2);
        vector<ll> vs=vector<ll>(n,0);
        build(1,0,n,vs);
    }
};

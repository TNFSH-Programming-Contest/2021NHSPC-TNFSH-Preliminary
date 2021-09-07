#include<bits/stdc++.h>
using namespace std;

#define endl '\n'
#define LC(i) (i << 1)
#define RC(i) ((i << 1) | 1)
#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
using ll  = long long;
using pii = pair <int, int>;
const ll INF = 0x7f7f7f7f7f7f7f7f; // 922337203685477580;
const int V = 200005;

int p[V], sz[V], b[V];
void init(int i) {
    p[i] = i;
    sz[i] = 1;
    b[i] = 0;
}
int find(int x) {
    return x == p[x] ? x : p[x] = find(p[x]);
}
void Union(int x, int y) {
    x = find(x), y = find(y);
    if (sz[x] < sz[y]) swap(x, y);
    p[y] = x;
    sz[x] += sz[y];
    b[x] = max(b[x], b[y]);
}


int node[V << 3];

void pull(int i) {
    int &li = node[LC(i)], &ri = node[RC(i)];
    if (b[find(li)] < b[find(ri)]) node[i] = ri;
    else node[i] = li;
}

void build(int i, int l, int r) {
    if (l == r) 
        return node[i] = l, void();
    int m = (l + r) >> 1;
    build(LC(i), l, m);
    build(RC(i), m + 1, r);
    pull(i);
}

void update(int i, int l, int r, int id) {
    if (id < l || r < id || l == r)
        return;
    int m = (l + r) >> 1;
    update(LC(i), l, m, id);
    update(RC(i), m + 1, r, id);
    pull(i);
}

int query(int i, int l, int r, int ql, int qr) {
    if (qr < l || r < ql)
        return -1;
    if (ql <= l && r <= qr)
        return node[i];
    int m = (l + r) >> 1;
    int li = query(LC(i), l, m, ql, qr);
    int ri = query(RC(i), m + 1, r, ql, qr);
    if (li == -1) return ri;
    if (ri == -1) return li;
    if (b[find(li)] < b[find(ri)]) return ri;
    else return li;
}


int arr[V];
pii a[V];

void solve() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
        cin >> arr[i], a[i] = pii(arr[i], i), init(i);

    sort(a, a + n);
    build(1, 0, n - 1);

    for (int j = 0; j < n; ++j) {
        int &val = a[j].first;
        int &i = a[j].second;

        int id = query(1, 0, n - 1, max(0, i - k + 1), min(n - 1, i + k - 1));
        int rnk = b[find(id)];
        if (rnk && val == arr[id]) 
            Union(i, id);
        else 
            rnk = rnk + 1;

        b[find(i)] = rnk;
        update(1, 0, n - 1, i);
    }

    for (int i = 0; i < n; ++i)
        cout << b[find(i)] << ' ';
    cout << endl;
}

signed main () {
    IOS;
    solve();
}


// 7 10 1 8 9 4 3 2 6 5

// 10 2
// 7 9 1 7 9 3 3 1 5 5

// Output
// 1 2 1 2 3 1 1 1 2 2 

// Expected
// 1 2 1 2 3 2 2 1 2 2
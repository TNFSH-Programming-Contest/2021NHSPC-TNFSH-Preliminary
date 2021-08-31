#include<bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define ALL(x) x.begin(), x.end()
#define CLR(x, y) memset(x, y, sizeof(x))

#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)

using ll  = long long;
using pii = pair <int, int>;

const ll INF = 0x7f7f7f7f7f7f7f7f; // 922337203685477580;
const int V = 200005;

int p[V];
int find(int x) {
    return x == p[x] ? x : p[x] = find(p[x]);
}
void Union(int x, int y) {
    p[find(y)] = find(x);
}

/* Main Code */

pii a[V];
set <pii> s;
int in[V];
vector <int> g[V];
void make_edge(int from, int to) {
    from = find(from), to = find(to);
    g[from].emplace_back(to);
    ++in[to];
}
bool inq[V];
int dp[V];

void solve() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
        cin >> a[i].first, p[i] = a[i].second = i;
    
    for (int l = 0, i = 0; i < n; ++i) {
        if (i - l == k) {
            s.erase(a[l]);
            ++l;
        }
        if (s.empty()) {
            s.insert(a[i]);
            continue;
        }
        auto it = s.lower_bound(pii(a[i].first, 0));
        if (it == s.end()) {
            --it;
            make_edge(it->second, a[i].second);
        }
        else if (it->first == a[i].first) {
            Union(it->second, a[i].second);
        }
        else if (it == s.begin()) {
            make_edge(a[i].second, it->second);
        }
        else {
            int to = it->second;
            --it;
            make_edge(it->second, a[i].second);
            make_edge(a[i].second, to);
        }
        s.insert(a[i]);
    }

    queue <int> q;
    for (int i = 0; i < n; ++i)
        if (!inq[find(i)] && !in[find(i)])
            inq[find(i)] = 1, q.push(find(i));

    while (!q.empty()) {
        int i = q.front(); q.pop();
        for (int j : g[i]) {
            dp[j] = max(dp[j], dp[i] + 1);
            --in[j];
            if (!in[j]) q.push(j);
        }
    }

    for (int i = 0; i < n; ++i)
        cout << dp[find(i)] + 1 << ' ';
    cout << endl;
}

signed main () {
    IOS;
    solve();
}
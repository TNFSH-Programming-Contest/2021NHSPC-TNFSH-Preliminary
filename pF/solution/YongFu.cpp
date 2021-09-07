#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define rep(i, a, b) for(int i = a; i < b; i++)

const int MAX_N = 1e6 + 5;
const int INF = 0x3fffffff;
int n, k;
int arr[MAX_N];

struct Node{
    vector<int> next;
    int val;
    Node():val(0){}
}node[MAX_N];

int DSU[MAX_N];
void Init(int x){
    rep(i, 0, x){
        DSU[i] = i;
    }
}
int Find(int x){
    return DSU[x] == x ? x : DSU[x] = Find(DSU[x]);
}
void Union(int a, int b){
    DSU[Find(b)] = Find(a);
    return;
}
void DFS(int x){
    if(node[Find(x)].val != 0){
        return;
    }
    // if(node[Find(x)].next.empty()){
    //     node[Find(x)].val = 1;
    //     return;
    // }
    int Max = 0;
    for(auto i : node[Find(x)].next){
        DFS( Find(i) );
        Max = max(node[Find(i)].val, Max);
    }
    node[Find(x)].val = Max + 1;
    return;
}
int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    

    cin >> n >> k;
    // set<int> s;
    Init(n);
    rep(i, 0, n){
        cin >> arr[i];
    }
    
    map<int, int> dict;
    rep(i, 0, n){
        if(dict.count(arr[i]) && dict[ arr[i] ] + k > i){
            Union(dict[ arr[i] ], i);
        }
        dict[ arr[i] ] = i;
    }
    // rep(i, 0, n){
    //     cout << Find(i) << ' ';
    // }
    // cout << endl;

    set<pii> s;
    s.insert({-INF, -1});
    s.insert({INF, n});
    rep(i, 0, n){
        if(i >= k){
            s.erase({arr[i - k], i - k});
        }
        auto a = --s.lower_bound({arr[i], 0});
        auto b = s.upper_bound({arr[i], INF});
        if(a->first != -INF){
            node[Find(i)].next.emplace_back(Find(a->second));
        }
        if(b->first != INF){
            node[Find(b->second)].next.emplace_back(Find(i));
        }
        s.insert({arr[i], i});
    }
    rep(i, 0, n){
        // cout << i;
        // for(auto j : node[Find(i)].next){
        //     cout << ' ' << j;
        // }
        // cout << endl;
        if(node[Find(i)].val == 0){
            DFS(Find(i));
        }
    }
    rep(i, 0, n - 1){
        cout << node[Find(i)].val << ' ';
    }
    cout << node[Find(n - 1)].val << '\n';
    return 0;
}
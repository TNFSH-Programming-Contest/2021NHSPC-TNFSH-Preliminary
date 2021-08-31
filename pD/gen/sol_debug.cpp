#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main()
{
    clock_t start_time = clock();
    
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n, k;
    cin >> n >> k;
    
    vector<int> v(n);
    for (int i=0; i<n; i++)
    {
        cin >> v[i];
    }
    
    set<int> vset;
    for (int i=0; i<n; i++)
    {
        vset.insert(v[i]);
    }
    
    vector<int> prf(n);
    for (int i=0; i<n; i++)
    {
        prf[i] += v[i] + (i? prf[i-1]: 0);
        prf[i] %= k;
    }
    
    pair<int, int> mxslen = {-1, -1};
    map<int, int> lastMet;
    
    int mxs = 0;
    set<int> pfset;
    for (int i=0; i<n; i++)
    {
        auto it = pfset.lower_bound(k - prf[i]);
        
        if (it == pfset.begin() || *prev(it) >= (k-prf[i]))
        {
            mxs = max(mxs, prf[i]);
            mxslen = max(mxslen, {prf[i], -(i+1)});
        }
        else
        {
            mxs = max(mxs, prf[i] + *prev(it));
            
            int key = *prev(it);
            mxslen = max(mxslen, {prf[i] + *prev(it), lastMet[key] - i});
        }
        
        pfset.insert(k - prf[i]);
        lastMet[k - prf[i]] = i;
    }
    
    cout << mxs << '\n';
    
    cerr << "N = " << n << ", ";
    cerr << "K = " << k << ", ";
    cerr << "ans = " << mxs << ", ";
    cerr << "uniq_num = " << vset.size() << ", ";
    cerr << "min_ans_len = " << -mxslen.second << ", ";
    cerr << fixed << setprecision(2) << "time = " << (1.0 * (clock() - start_time) / CLOCKS_PER_SEC) << "\n";
}

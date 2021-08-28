#include <bits/stdc++.h>
using namespace std;

//#define int long long

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n, k;
    cin >> n >> k;
    
    vector<int> v(n);
    for (int i=0; i<n; i++)
    {
        cin >> v[i];
    }
    
    vector<int> prf(n);
    for (int i=0; i<n; i++)
    {
        prf[i] += v[i] + (i? prf[i-1]: 0);
        prf[i] %= k;
    }
    
    int mxs = 0;
    set<int> pfset;
    for (int i=0; i<n; i++)
    {
        auto it = pfset.lower_bound(k - prf[i]);
        
        if (it == pfset.begin() || *prev(it) >= (k-prf[i]))
        {
            mxs = max(mxs, prf[i]);
        }
        else
        {
            mxs = max(mxs, prf[i] + *prev(it));
        }
        
        pfset.insert(k - prf[i]);
    }
    
    cout << mxs << '\n';
}

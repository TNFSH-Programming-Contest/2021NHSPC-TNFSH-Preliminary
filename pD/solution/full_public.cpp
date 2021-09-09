#include <bits/stdc++.h>
using namespace std;

int main()
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
    
    vector<int> S(n);
    for (int i=0; i<n; i++)
    {
        S[i] += v[i] + (i? S[i-1]: 0);
        S[i] %= k;
    }
    
    int ans = 0;
    set<int> bst;
    for (int j=0; j<n; j++)
    {
        auto it = bst.lower_bound(k - S[j]);
        
        if (it == bst.begin() || *prev(it) >= (k-S[j]))
        {
			// "0 < -S[i-1] < K-S[j]" does not exist
            ans = max(ans, S[j]);
        }
        else
        {
            ans = max(ans, S[j] + *prev(it));
        }
        
        bst.insert(k - S[j]);
    }
    
    cout << ans << '\n';
}

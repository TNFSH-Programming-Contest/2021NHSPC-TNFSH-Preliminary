#pragma GCC optimize "O3"
#include <bits/stdc++.h>
using namespace std;

// #define int long long

mt19937 mt;

signed main()
{
    clock_t start_time = clock();
    mt = mt19937(clock());
    
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n, k;
    cin >> n >> k;
    
    vector<int> v(n);
    for (int i=0; i<n; i++)
    {
        cin >> v[i];
    }
    
    int *prf = new int[n]{};
    for (int i=0; i<n; i++)
    {
        prf[i] = v[i] + (i? prf[i-1]: 0);
        prf[i] %= k;
    }
    
    int mxs = 0;
	for (int i=0; i<n; i++)
	{
		mxs = max(mxs, v[i]%k);
		mxs = max(mxs, prf[i]%k);
		mxs = max(mxs, (k + prf[n-1] - (i? prf[i-1]: 0))%k);
	}
	
    while (clock() - start_time <= CLOCKS_PER_SEC * 1.85)
    {
        int i = mt()%n, j = mt()%n;
        if (i > j)
        {
            swap(i, j);
        }
        
        int sum = prf[j] - (i? prf[i-1]: 0);
        mxs = max(mxs, (sum<0? sum+k: sum));
    }
    
    cout << mxs << '\n';
}

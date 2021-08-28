#pragma GCC optimize "O3"
#include <bits/stdc++.h>
using namespace std;

#define int long long

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
    
    int mxs = 0;
    while (clock() - start_time <= CLOCKS_PER_SEC * 2.85)
    {
        int i = mt()%n, j = mt()%n;
        if (i > j)
        {
            swap(i, j);
        }
        
        int sum = 0;
        for (int X=i; X<=j; X++)
        {
            sum += v[X];
            sum %= k;
        }
        
        mxs = max(mxs, sum);
    }
    
    cout << mxs << '\n';
}

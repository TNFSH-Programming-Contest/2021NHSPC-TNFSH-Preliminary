#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int u[] = {1, 1}, v[] = {0, 0};
    
    auto calc = [&](int i, int k) -> int
    {
        return k*u[i] + v[i];
    };
    
    int Q;
    cin >> Q;
    for (int qi=0; qi<Q; qi++)
    {
        int qx;
        cin >> qx;
        
        if (qx == 1)
        {
            int k;
            cin >> k;
            
            cout << max(calc(0, k), calc(1, k)) << "\n";
        }
        else if (qx == 2)
        {
            int i, a;
            char op;
            cin >> i >> op >> a, --i;
            
            if (op == '+')
            {
                v[i] += a;
            }
            else if (op == '*')
            {
                u[i] *= a, v[i] *= a;
            }
        }
        else if (qx == 3)
        {
            int den = v[0] - v[1], nom = u[1] - u[0];
            
            if ((nom == 0) || (den % nom != 0))
            {
                cout << "no\n";
            }
            else
            {
                int m = den / nom;
                cout << m << "\n";
            }
        }
    }
}

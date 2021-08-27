#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int ac[] = {1, 1}, bc[] = {0, 0};
    
    auto calc = [&](int i, int k) -> int
    {
        return k*ac[i] + bc[i];
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
            int i, y;
            char op;
            cin >> i >> op >> y, --i;
            
            if (op == '+')
            {
                bc[i] += y;
            }
            else if (op == '*')
            {
                ac[i] *= y, bc[i] *= y;
            }
        }
        else if (qx == 3)
        {
            int den = bc[0] - bc[1], nom = ac[1] - ac[0];
            
            if ((nom == 0) || (den % nom != 0))
            {
                cout << "no\n";
            }
            else
            {
                cout << den / nom << "\n";
            }
        }
    }
}

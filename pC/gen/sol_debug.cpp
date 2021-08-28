#include <bits/stdc++.h>
using namespace std;

int main()
{
    clock_t start_time = clock();
    
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int routeLen[] = {0, 0};
    int sumBrute = 0;
    int sumq[] = {0, 0, 0, 0};
    
    int ac[] = {1, 1}, bc[] = {0, 0};
    
    auto calc = [&](int i, int k) -> int
    {
        return k*ac[i] + bc[i];
    };
    
    map<string, int> q2map;
    
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
            
            sumBrute += routeLen[0] + routeLen[1];
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
            
            routeLen[i]++;
            q2map[string() + "12"[i] + op]++;
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
        
        
        assert( -10000 <= ac[0] && ac[0] <= 10000 );
        assert( -10000 <= ac[1] && ac[1] <= 10000 );
        assert( -100000000 <= bc[0] && bc[0] <= 100000000 );
        assert( -100000000 <= bc[1] && bc[1] <= 100000000 );
        sumq[qx]++;
    }
    
    double elapsedTime = (1.0 * (clock() - start_time) / CLOCKS_PER_SEC);
    
    cerr << "Q = " << Q << ", ";
    cerr << "sumBrute = " << sumBrute << ", ";
    
    cerr << "q2 = {";
    for (auto it : q2map)
    {
        cerr << it.first << ": " << it.second << ", ";
    }
    cerr << "}, ";
    
    cerr << "sumqx = {" << sumq[1] << ", " << sumq[2] << ", " << sumq[3] << "}, ";
    cerr << fixed << setprecision(2) << "time = " << elapsedTime << ", "<< "\n";
}

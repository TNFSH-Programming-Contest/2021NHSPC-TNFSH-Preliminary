#include <bits/stdc++.h> 
using namespace std; 
  
struct segtree { 
    int N; 
    vector<int> sgv; 
      
    int update(int ui, int uv, int sgl, int sgr, int sgi) { 
        if (ui < sgl || ui > sgr) return sgv[sgi]; 
        else if (sgl == sgr) return sgv[sgi] = uv; 
        else { 
            int m = (sgl + sgr) >> 1; 
            return sgv[sgi] = max(update(ui, uv, sgl, m, sgi << 1), update(ui, uv, m+1, sgr, (sgi << 1) | 1)); 
        } 
    } 
      
    int update(int ui, int uv) { 
        return update(ui, uv, 0, N-1, 1); 
    } 
      
    int query(int ql, int qr, int sgl, int sgr, int sgi) { 
        if (qr < sgl || ql > sgr) return 0; 
        else if (ql <= sgl && sgr <= qr) return sgv[sgi]; 
        else { 
            int m = (sgl + sgr) >> 1; 
            return max(query(ql, qr, sgl, m, sgi << 1), query(ql, qr, m+1, sgr, (sgi << 1) | 1)); 
        } 
    } 
      
    int query(int ql, int qr) { 
        return query(ql, qr, 0, N-1, 1); 
    } 
      
    segtree(int N): N(N), sgv(N<<2) {} 
}; 
  
int main() 
{ 
    ios::sync_with_stdio(0); 
    cin.tie(0); 
      
    int n, k; 
    cin >> n >> k; 
    
/* Handle Input */
vector<int> v(n); 
map<int, vector<int>> valmp; 
for (int i=0; i<n; ++i) { 
    cin >> v[i]; 
    valmp[v[i]].push_back(i); 
} 
    
segtree st(n); 
auto test = [&](int i) { 
    int L = max(0, i-(k-1)); 
    int R = min(n-1, i+(k-1)); 
    return st.query(L, R); 
}; 
    
/* Solve */
vector<int> ans(n); 
for (auto &it: valmp) { // Handle the same a_i
    vector<int> &ids = it.second; 
    int vn = ids.size(); 
        
    for (int i=0, j; i<vn; i=j) {  // two pointer method
        int mxlow = test(ids[i]); 
        for (j=i+1; j<vn && ids[j]-ids[j-1]+1 <= k; j++) { 
            int vi = ids[j]; 
            mxlow = max(mxlow, test(vi)); // query the extreme value
        } 
            
        for (int jj=i; jj<j; jj++) { 
            int vi = ids[jj]; 
            ans[vi] = mxlow+1, st.update(vi, mxlow+1); // find answer and update seg tree
        } 
    } 
} 
      
    for (int x : ans) cout << x << ' '; 
    cout << '\n'; 
} 

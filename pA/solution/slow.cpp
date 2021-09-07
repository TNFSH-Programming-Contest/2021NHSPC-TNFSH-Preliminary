#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<ll,ll>
#define fi first
#define se second
#define vi vector<ll>
#define pb emplace_back
#define all(n) (n).begin(),(n).end()
#define mem(n,x) memset(n,x,sizeof(n))
#define IOS ios::sync_with_stdio(0),cin.tie(0)
#define dbg(...) cerr<<#__VA_ARGS__<<" = ";_do(__VA_ARGS__);
template<typename T> void _do(T x){cerr<<x<<"\n";}
template<typename T,typename ...U> void _do(T x,U ...y){cerr<<x<<", ";_do(y...);}

ll N, Q, arr[1000005], ql[1000005], qr[1000005];

signed main(){
    //IOS;
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> arr[i];
    cin >> Q;
    for(int i = 1; i <= Q; i++){
        cin >> ql[i] >> qr[i];
    }
    for(int i = 1; i <= Q; i++){
        cout << arr[(ql[i] + qr[i]) / 2] << endl;
    }
}

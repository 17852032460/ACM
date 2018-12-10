#include <iostream> 
#include <cstdio> 
#include <algorithm> 
#include <cmath> 

using namespace std; 

typedef long long int ll; 

ll mod = 998244353; 
ll q[60], p[60]; 

ll qpow(ll x, ll y) 
{ 
    ll res = 1; 
    x %= mod; 
    while(y) 
    {
        if(y & 1) 
            res = (res * x) % mod; 
            x = (x * x) % mod; 
            y >>= 1; 
    } 
    return res % mod; 
} 

int main() 
{ 
    //freopen("in.txt", "r", stdin); 
    int t; 
    cin >> t; 
    while(t --) 
    {
        int m;
        cin >> m; 
        for(int i = 1; i <= m; ++ i) 
        { 
            cin >> p[i] >> q[i]; 
        } 
        ll ans = 1; 
        for(int i = 1; i <= m; ++ i) 
        { 
            ll mul = qpow(p[i], q[i] - 1); 
            mul %= mod; 
            ll cnt = 1; //原谅我这里写的这么乱，项数太多取膜取晕了QAQ 
            cnt = (cnt * p[i]) % mod; 
            cnt = (cnt + (p[i] * q[i]) % mod) % mod; 
            cnt = (cnt - q[i] + mod) % mod; 
            cnt = (cnt * mul) % mod; 
            ans = (ans * cnt) % mod; //cnt就是一对p、q按公式推出来的，然后在这里乘起来     
         } 
         cout << ans << endl;
    }
    return 0;
}

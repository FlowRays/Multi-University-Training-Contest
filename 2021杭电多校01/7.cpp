// https://www.cnblogs.com/ZX-GO/p/15039734.html

#include <bits/stdc++.h>

#define forn(i, n) for (ll i = 0; i < ll(n); i++)
#define fore(i, l, r) for (ll i = ll(l); i <= ll(r); ++i)
#define endl "\n"
#define pii pair<ll,ll>
#define all(x) x.begin(),x.end()
#define pb push_back
#define vi vector<ll>

using namespace std;
using ll = long long;
using ull = unsigned long long;

const ll inf = 0x3f3f3f3f;
const ll mod = 998244353;
const ll N = 1e5+10;

ll qpow(ll a,ll b){
    ll res = 1;
    while(b){
        if(b&1) res = res*a%mod;
        a = a*a%mod;
        b >>= 1;
    }
    return res;
}

ll bsgs(ll a,ll b,ll p){
    if(1%p == b%p) return 0;
    ll k = sqrt(p)+1;
    unordered_map<ll,ll> hash;
    for(ll i=0,j=b%p;i<k;++i){
        hash[j] = i;
        j = j*a%p;
    }
    ll ak = qpow(a,k);
    for(ll i=1,j=ak;i<=k;++i){
        if(hash.count(j)) return i*k-hash[j];
        j = j*ak%p;
    }
    return -1;
}

void solve(){
    ll n,x;
    cin>>n>>x;
    if(x == 0){
        cout<<1<<endl;
        return;
    }
    if(x == 1){
        cout<<0<<endl;
        return;
    }
    ll r1 = bsgs(n-1,(n*x+(n-1)+mod)%mod,mod);
    ll r2 = bsgs(n-1,(n*x-(n-1)+mod)%mod,mod);
    if(r1%2==0) r1 = -1;
    if(r2%2==1) r2 = -1;
    ll ans = -1;
    if(r1 != -1) ans = r1;
    if(r2 != -1){
        if(ans == -1) ans = r2;
        else ans = min(ans,r2);
    }
    cout<<ans<<endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll tt;
    cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}
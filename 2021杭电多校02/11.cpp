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

void solve(){
    ll n;
    cin>>n;
    vi a(n),b(n);
    vector<vector<ll>> va(n,vi(2)),vb(n,vi(2));
    forn(i,n) cin>>a[i], va[i][0] = va[i][1] = a[i];
    forn(i,n) cin>>b[i], vb[i][0] = vb[i][1] = b[i];
    for(int i=n-1;i>=0;--i){
        ll val = 0;
        for(ll j=0;j<=18;++j){
            if((i>>j&1) == 0) val = i | (1<<j);
            else continue;
            if(val>=n) continue;
            va[i][0] = max(va[i][0],va[val][0]);
            va[i][1] = min(va[i][1],va[val][1]);
            vb[i][0] = max(vb[i][0],vb[val][0]);
            vb[i][1] = min(vb[i][1],vb[val][1]);
        }
    }
    ll t = -1e18;
    ll ans = 0;
    for(ll i=n-1;i>=0;--i){
        for(int j=0;j<2;++j){
            for(int k=0;k<2;++k){
                t = max(t,va[i][j]*vb[i][k]);
            }
        }
        ans = (ans+t%mod+mod)%mod;
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
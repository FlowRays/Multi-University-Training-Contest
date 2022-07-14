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
const ll mod = 1e9+7;
const ll N = 1e5+10;

ll qpow(ll x,ll y){
    ll res = 1;
    while(y){
        if(y&1) res = res*x%mod;
        x = x*x%mod;
        y >>= 1;
    }
    return res;
}

void solve(){
    ll n;
    string s;
    cin>>n>>s;
    ll t = 0;
    for(ll i=1;i<n;++i){
        if(s[i] == s[i-1]) t++;
        else break;
    }
    cout<<qpow(2,t)<<endl;
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
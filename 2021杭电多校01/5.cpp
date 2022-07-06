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
const ll N = 1e7+10;

ll primes[N],st[N],cnt,s[N];

void init(){
    for(ll i=2;i<N;++i){
        if(!st[i]) primes[cnt++] = i;
        for(ll j=0;primes[j]*i<N;++j){
            st[primes[j]*i] = 1;
            if(i%primes[j]==0) break;
        }
    }
    for(ll i=1;i<=cnt;++i) s[i] = s[i-1]+primes[i-1];
}

void solve(){
    ll n;
    cin>>n;
    ll l = 0, r = cnt-1;
    while(l<r){
        ll mid = l+r+1 >> 1;
        if(primes[mid]<=n) l=mid;
        else r=mid-1;
    }
    // cout<<l<<endl;
    cout<<(2+n)*(n-1)/2+s[l+1]-4<<endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();
    ll tt;
    cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}
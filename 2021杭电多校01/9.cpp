#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define fore(i, l, r) for (int i = int(l); i <= int(r); ++i)
#define endl "\n"
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define pb push_back
#define vi vector<int>

using namespace std;
using ll = long long;
using ull = unsigned long long;

const int inf = 0x3f3f3f3f;
const int mod = 1e9+7;
const int N = 1e5+10;

int f[N];

int find(int x){
    if(x == f[x]) return x;
    return f[x] = find(f[x]);
}

void solve(){
    int n,m,k;
    cin>>n>>m>>k;
    map<int,vector<pii>> e;
    int mi = 1e9;
    forn(i,m){
        int a,b,w;
        cin>>a>>b>>w;
        e[w].pb({a,b});
        mi = min(mi,w);
    }
    fore(i,1,n) f[i] = i;
    int tot = n;
    if(k == n){
        cout<<0<<endl;
        return;
    }
    for(auto tmp: e){
        auto x = tmp.first;
        auto v = tmp.second;
        for(auto pi: v){
            int a = pi.first, b = pi.second;
            int pa = find(a), pb = find(b);
            if(pa != pb){
                f[pa] = pb;
                tot--;
            }
        }
        if(tot == k){
            cout<<x<<endl;
            return;
        }
    }
    cout<<-1<<endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}
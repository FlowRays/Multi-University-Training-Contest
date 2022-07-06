#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define fore(i, l, r) for (int i = int(l); i <= int(r); ++i)
#define endl "\n"
#define pii pair<int,int>
#define aint(x) x.begin(),x.end()
#define pb push_back
#define vi vector<int>

using namespace std;
using ll = long long;
using ull = unsigned long long;

const int inf = 0x3f3f3f3f;
const int mod = 1e9+7;
const int N = 1e5+10;

void solve(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> v(n,vector<int>(m));
    vector<vector<pii>> t(n,vector<pii>(m));
    forn(i,n){
        forn(j,m){
            cin>>v[i][j];
        }
    }
    forn(j,m){
        int i = 0;
        while(i<n){
            int l = i, r = i;
            while(r+1<n && v[r][j]<=v[r+1][j]) r++;
            fore(k,l,r) t[k][j] = {l,r};
            i = r+1;
        }
    }
    int ans = 0;
    forn(i,n){
        stack<pii> stk;
        vi a(m+2,-1);
        vi l(m+1),r(m+1);
        forn(j,m) a[j+1] = t[i][j].second;
        forn(j,m+1){
            while(stk.size() && stk.top().first>=a[j]){
                stk.pop();
            }
            if(j>0) l[j] = stk.top().second;
            stk.push({a[j],j});
        }
        stk = stack<pii>();
        for(int j=m+1;j>0;--j){
            while(stk.size() && stk.top().first>=a[j]){
                stk.pop();
            }
            if(j<m+1) r[j] = stk.top().second;
            stk.push({a[j],j});
        }
        fore(j,1,m){
            ans = max(ans,(a[j]-i+1)*(r[j]-l[j]-1));
        }
    }
    cout<<ans<<endl;
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
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

void solve(){
    int n,m;
    cin>>n>>m;
    vi f(n+1);
    forn(i,n) cin>>f[i+1],f[i+1]++;
    vector<tuple<int,int,int,int,int>> q(m);
    forn(i,m){
        int x0,y0,x1,y1;
        cin>>x0>>y0>>x1>>y1;
        y0++,y1++;
        q[i] = make_tuple(i,x0,y0,x1,y1);
    }
    // 在x方向上做莫队，分块维护y坐标
    int len = sqrt(n);
    auto get = [&](int x){
        return x/len;
    };
    sort(all(q),[&](const tuple<int,int,int,int,int> &a,const tuple<int,int,int,int,int> &b){
        int i = get(std::get<1>(a)), j = get(std::get<1>(b));
        if(i != j) return i<j;
        return std::get<3>(a)<std::get<3>(b);
    });
    vi c(1e6+10),sum(1e6+10),Y(1e6+10); // 记录出现次数
    auto add_sq = [&](int x,int v){
        c[x] += v;
        sum[x/len] += v;
    };
    auto get_sq = [&](int x){
        int res = 0;
        for(int i=x/len*len;i<=x;++i) res += c[i];
        for(int i=0;i<x/len;++i) res += sum[i];
        return res;
    };
    auto add = [&](int pos){
        if(!Y[f[pos]]) add_sq(f[pos],1);
        Y[f[pos]]++;
    };
    auto del = [&](int pos){
        Y[f[pos]]--;
        if(!Y[f[pos]]) add_sq(f[pos],-1);
    };
    vi ans(m);
    for(int k=0,i=0,j=1;k<m;++k){
        // i表示r,j表示l
        auto id = std::get<0>(q[k]);
        auto x0 = std::get<1>(q[k]);
        auto y0 = std::get<2>(q[k]);
        auto x1 = std::get<3>(q[k]);
        auto y1 = std::get<4>(q[k]);
        while(i<x1) add(++i);
        while(i>x1) del(i--);
        while(j<x0) del(j++);
        while(j>x0) add(--j);
        ans[id] = get_sq(y1)-get_sq(y0-1);
    }
    forn(i,m) cout<<ans[i]<<endl;
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
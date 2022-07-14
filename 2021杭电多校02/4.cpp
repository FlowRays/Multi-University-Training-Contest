// 莫队 + 分块

#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define fore(i, l, r) for (int i = int(l); i <= int(r); ++i)
#define sz(a) int((a).size())
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,q;
    cin>>n;
    vi c(n+1);
    forn(i,n) cin>>c[i+1];
    cin>>q;
    vector<tuple<int,int,int,int,int>> Q(q);
    forn(i,q){
        int l,r,a,b;
        cin>>l>>r>>a>>b;
        Q[i] = make_tuple(l,r,a,b,i);
    }
    int len = sqrt(n+1);
    auto get = [&](int x){
        return x/len;
    };
    sort(all(Q),[&](const tuple<int,int,int,int,int> &a, const tuple<int,int,int,int,int> &b){
        int i = get(std::get<0>(a)), j = get(std::get<0>(b));
        if(i != j) return i<j;
        return std::get<1>(a)<std::get<1>(b);
    });
    vi cnt(n+1),cc(n*2),sum((2*n+len-1)/len+1);
    auto add = [&](int x){
        cnt[c[x]]++;
        if(cnt[c[x]]>1) return;
        int v = c[x];
        cc[v]++;
        sum[v/len]++;
    };
    auto del = [&](int x){
        cnt[c[x]]--;
        if(cnt[c[x]]>0) return;
        int v = c[x];
        cc[v]--;
        sum[v/len]--;
    };
    auto query = [&](int x){
        int res = 0;
        for(int i=x/len*len;i<=x;++i) res += cc[i];
        for(int i=0;i<x/len;++i) res += sum[i];
        return res;
    };
    auto search = [&](int a,int b){
        int res = 0;
        int s = 0;
        for(int i=16;i>=0;--i){
            int va = a>>i&1, vb = b>>i&1;
            if(vb){
                res += query(s+(va<<i)+(1<<i)-1)-query(s+(va<<i)-1);
                s |= ((!va)<<i);
            }
            else s |= (va<<i);
        }
        res += cc[a^b];
        return res;
    };
    vi ans(q);
    for(int k=0,i=0,j=1;k<q;++k){
        int l = std::get<0>(Q[k]);
        int r = std::get<1>(Q[k]);
        int a = std::get<2>(Q[k]);
        int b = std::get<3>(Q[k]);
        int id = std::get<4>(Q[k]);
        while(i<r) add(++i);
        while(i>r) del(i--);
        while(j<l) del(j++);
        while(j>l) add(--j);
        ans[id] = search(a,b);
    }
    forn(i,q) cout<<ans[i]<<endl;

    return 0;
}

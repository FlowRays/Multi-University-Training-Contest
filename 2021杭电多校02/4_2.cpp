// 字典树+BIT

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

struct Query{
    int l,r,a,b,id;
};

int tr[N*400][2],rt[N],idx,cnt[N*400];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    vi v(n+1);
    forn(i,n) cin>>v[i+1];
    int m;
    cin>>m;
    vector<Query> q(m);
    forn(i,m){
        cin>>q[i].l>>q[i].r>>q[i].a>>q[i].b;
        q[i].id = i;
    }
    sort(all(q),[&](const Query &a, const Query &b){
        if(a.r != b.r) return a.r<b.r;
        return a.l<b.l;
    });
    auto insert = [&](int &p,int x,int v){
        if(!p) p = ++idx;
        int s = p;
        for(int i=16;i>=0;--i){
            int &t = tr[s][x>>i&1];
            if(!t) t = ++idx;
            s = t;
            cnt[s] += v;
        }
    };
    auto query = [&](int p,int a,int b){
        int res = 0;
        for(int i=16;i>=0;--i){
            int va = a>>i&1, vb = b>>i&1;
            if(vb) res += cnt[tr[p][va]];
            p = tr[p][va^vb];
        }
        res += cnt[p];
        return res;
    };
    auto add = [&](int x,int val){
        for(int i=x;i<=n;i += i&-i){
            insert(rt[i],v[x],val);
        }
    };
    auto get = [&](int x,int a,int b){
        int res = 0;
        for(int i=x;i>=1;i -= i&-i){
            res += query(rt[i],a,b);
        }
        return res;
    };
    int pos = 1;
    vi vis(n+1),ans(m);
    for(auto t: q){
        int l = t.l, r = t.r, a = t.a, b = t.b, id = t.id;
        while(pos<=r){
            if(vis[v[pos]]) add(vis[v[pos]],-1);
            add(pos,1);
            vis[v[pos]] = pos;
            pos++;
        }
        ans[id] = get(r,a,b)-get(l-1,a,b);
    }
    forn(i,m) cout<<ans[i]<<endl;

    return 0;
}
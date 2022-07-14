// https://vjudge.net/problem/HDU-6962
// 树剖+线段树维护二次函数(pos-x)^2

#include <bits/stdc++.h>

#define forn(i, n) for (ll i = 0; i < ll(n); i++)
#define fore(i, l, r) for (ll i = ll(l); i <= ll(r); ++i)
#define sz(a) ll((a).size())
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

ll n,m;
ll id[N],cnt;
ll dep[N],sz[N],top[N],fa[N],son[N];
vector<ll> e[N];

void dfs1(ll u,ll father,ll depth){
    dep[u] = depth, fa[u] = father, sz[u] = 1;
    for(auto j: e[u]){
        if(j == father) continue;
        dfs1(j,u,depth+1);
        sz[u] += sz[j];
        if(sz[son[u]]<sz[j]) son[u] = j;
    }
}

void dfs2(ll u,ll t){
    id[u] = ++cnt, top[u] = t;
    if(!son[u]) return;
    dfs2(son[u],t);
    for(auto j: e[u]){
        if(j == fa[u] || j == son[u]) continue;
        dfs2(j,j);
    }
}

struct Node{
    ll l,r;
    ll sum_pos1,sum_pos2,tot;
    ll lazy1,lazy2,lazy3;
}tr[N*4];

void pushup(ll u){
    tr[u].sum_pos1 = tr[u<<1].sum_pos1 + tr[u<<1|1].sum_pos1;
    tr[u].sum_pos2 = tr[u<<1].sum_pos2 + tr[u<<1|1].sum_pos2;
    tr[u].tot = tr[u<<1].tot + tr[u<<1|1].tot;   
}

void pushdown(Node &t,ll lazy1,ll lazy2,ll lazy3){
    if(!lazy1 && !lazy2 && !lazy3) return;
    t.tot += t.sum_pos2*lazy1;
    t.tot -= 2*t.sum_pos1*lazy2;
    t.tot += (t.r-t.l+1)*lazy3;
    t.lazy1 += lazy1;
    t.lazy2 += lazy2;
    t.lazy3 += lazy3;
}

void pushdown(ll u){
    auto &root = tr[u], &left = tr[u<<1], &right = tr[u<<1|1]; 
    pushdown(left,root.lazy1,root.lazy2,root.lazy3);
    pushdown(right,root.lazy1,root.lazy2,root.lazy3);
    root.lazy1 = root.lazy2 = root.lazy3 = 0;
}

void build(ll u,ll l,ll r){
    if(l == r){
        tr[u] = {l,r,l,l*l};
        return;
    }
    tr[u] = {l,r};
    ll mid = l+r >> 1;
    build(u<<1,l,mid), build(u<<1|1,mid+1,r);
    pushup(u);
}

void update(ll u,ll l,ll r,ll k){
    if(l<=tr[u].l && r>=tr[u].r){
        pushdown(tr[u],1,k,k*k);
        return;
    }
    pushdown(u);
    ll mid = tr[u].l + tr[u].r >> 1;
    if(l<=mid) update(u<<1,l,r,k);
    if(r>mid) update(u<<1|1,l,r,k);
    pushup(u);
}

ll query(ll u,ll l,ll r){
    if(l<=tr[u].l && r>=tr[u].r) return tr[u].tot;
    pushdown(u);
    ll mid = tr[u].l + tr[u].r >> 1;
    ll res = 0;
    if(l<=mid) res = query(u<<1,l,r);
    if(r>mid) res += query(u<<1|1,l,r);
    return res;
}

int lca(int a, int b) {
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) swap(a, b);
		a = fa[top[a]];
	}
	return id[a] < id[b] ? a : b;
}

void update_path(ll a,ll b){
	int l = 1, r = dep[a] + dep[b] - 2 * dep[lca(a, b)] + 1; // 表示点的个数，从左/右
	while (top[a] != top[b]) {
		if (dep[top[a]] > dep[top[b]]) {
			update(1,id[top[a]], id[a], id[top[a]]-l);
			l += id[a] - id[top[a]] + 1; // 加入这条链的点[id[a],id[top[a]]]
			a = fa[top[a]];
		}
		else {
			update(1,id[top[b]], id[b], id[b]-r);
			r -= id[b] - id[top[b]] + 1; // 减去这条链的点[id[top[b]],id[b]]
			b = fa[top[b]];
		}
	}
	if (id[a] < id[b]) {
		update(1,id[a], id[b], id[a]-l);
	}
	else {
		update(1,id[b], id[a], id[b]+r);
	}
}

ll query_node(ll x){
    return query(1,id[x],id[x]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    forn(i,n-1){
        ll a,b;
        cin>>a>>b;
        e[a].pb(b);
        e[b].pb(a);
    }
    dfs1(1,-1,1);
    dfs2(1,1);
    build(1,1,n);
    cin>>m;
    while(m--){
        ll op,a,b;
        cin>>op>>a;
        if(op == 1){
            cin>>b;
            update_path(a,b);
        }
        else{
            cout<<query_node(a)<<endl;
        }
    }

    return 0;
}

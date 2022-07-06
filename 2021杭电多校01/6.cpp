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
const int M = 3e6+10;

int son[M][2],id[M][2]; // 记录trie结点的最大下标值

void solve(){
    int n,k;
    cin>>n>>k;
    // 可以用到的时候再初始化
    // memset(son,0,sizeof(int)*n*30*2);
    // memset(id,-1,sizeof(int)*n*30*2);
    son[0][0] = son[0][1] = 0;
    id[0][0] = id[0][1] = -1;
    int idx = 0;    // 注意初始化!!!
    vi a(n),s(n+1);
    forn(i,n) cin>>a[i], s[i+1] = s[i]^a[i];
    vi bit_k(30);
    for(int i=29;i>=0;--i) bit_k[i] = k>>i&1;
    auto insert = [&](int pos){
        int x = s[pos];
        int p = 0;
        for(int i=29;i>=0;--i){
            int &t = son[p][x>>i&1]; 
            id[p][x>>i&1] = max(id[p][x>>i&1],pos); // 记录trie结点的最大下标值
            if(!t){
                t = ++idx;
                son[idx][0] = son[idx][1] = 0;  // 用到的时候再初始化
                id[idx][0] = id[idx][1] = -1;
            }
            p = t;
        }
    };
    // 根据和k的每一位比较，返回异或值>=k的最大下标
    auto search = [&](int x){
        int res = -1;
        int p = 0;
        for(int i=29;i>=0;--i){
            int t = x>>i&1;
            if(!son[p][!t] && bit_k[i]) break;
            if(son[p][!t] && (!bit_k[i] || i==0)){
                res = max(res,id[p][!t]);
            }
            if(son[p][!t] && bit_k[i]) p = son[p][!t];
            else if(son[p][t] && !bit_k[i]){
                if(i == 0) res = max(res,id[p][t]);
                p = son[p][t];
            }
        }
        return res;
    };
    int ans = 1e9;
    pii p;
    insert(0);  // 把s[0]=0放入trie
    fore(i,1,n){
        int res = search(s[i]);
        if(res != -1){
            int len = i-res;
            if(len<ans){
                ans = len;
                p = {res+1,i};
            }
        }
        insert(i);
    }
    if(ans == 1e9) cout<<-1<<endl;
    else cout<<p.first<<" "<<p.second<<endl;
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
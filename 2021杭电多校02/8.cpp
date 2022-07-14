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
    int n;
    cin>>n;
    map<string,int> mp;
    forn(i,n){
        string s;
        cin>>s;
        mp[s] = i;
    }
    vector<vector<int>> v(n),w(n);
    int m;
    cin>>m;
    forn(i,m){
        string s;
        int x,y;
        cin>>s>>x>>y;
        int id = mp[s];
        w[id].pb(x);
        v[id].pb(y);
    }
    // 对每个课程做01背包，求出0-100分所需要的最少天数，存入s中
    vector<vector<int>> s(n,vector<int>(101,inf));
    forn(i,n){
        int len = v[i].size();
        int tot = accumulate(all(v[i]),0);
        vi dp(tot+1);
        for(int j=0;j<len;++j){
            for(int k=tot;k>=v[i][j];--k){
                dp[k] = max(dp[k],dp[k-v[i][j]]+w[i][j]);
            }
        }
        int pre = -1;
        for(int j=0;j<=tot;++j){
            if(dp[j]>pre){
                for(int k=pre+1;k<=min(100,dp[j]);++k){
                    s[i][k] = j;
                }
                pre = dp[j]; 
            }
            if(dp[j]>100) break;
        }
    }
    int t,p;
    cin>>t>>p;
    // 对所有课程做分组背包，每一组里的物品是0-100分，代表价值，最后加上一个维度表示挂科数量，初始化必须-inf
    vector<vector<vector<int>>> dp(n,vector<vector<int>>(t+1,vector<int>(p+1,-inf)));
    for(int i=0;i<n;++i){
        for(int j=0;j<=t;++j){
            for(int k=0;k<=100;++k){
                if(j>=s[i][k]){
                    int tt = (k>=60 ? 0 : 1);
                    for(int q=tt;q<=p;++q){
                        dp[i][j][q] = max(dp[i][j][q],(i>=1 ? dp[i-1][j-s[i][k]][q-tt]+k : k));
                    }
                }
            }
        }
    }
    // 注意这里的dp表示的是确切的花了j天，挂了k科，而不是小于等于的关系
    int ans = -inf;
    for(int j=0;j<=t;++j)
        for(int k=0;k<=p;++k) 
            ans = max(ans,dp[n-1][j][k]);
    cout<<(ans<=0 ? -1 : ans)<<endl;    // 可能会因为得0分只需要0天而被max到0
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
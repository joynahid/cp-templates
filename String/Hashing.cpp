//Submission: https://codeforces.com/contest/1326/submission/73993551

const ll MOD = 999995713;
const ll INF = 2000000000000000001LL;
const ld EPS = 1e-9;
const ll MAX = 3000005;
const ll bas = 811;
 
ll Hash[MAX], rHash[MAX];
ll pw[MAX];
 
ll inv(ll a, ll p)
{
    if(p == 0) return 1;
    ll tmp = inv(a,p/2)%MOD;
    
    if(p&1) return (((tmp*tmp)%MOD)*a)%MOD;
    return (tmp * tmp)%MOD;
}
 
string Find(string ns)
{
    ll N=ns.size();
        
    for(int i=0;i<N;i++)
        Hash[i+1] = Hash[i] + ((ns[i]-'a'+1)*pw[i])%MOD, Hash[i+1]%=MOD;
        
    reverse(ALL(ns));
 
    for(int i=0;i<N;i++)
        rHash[i+1] = rHash[i] + ((ns[i]-'a'+1)*pw[i])%MOD, rHash[i+1]%=MOD;
    
    string ans;
    for(int i=1;i<=N;i++)
    {
        ll nwHash = rHash[N]-rHash[i-1]+MOD;
        nwHash*= inv(pw[i-1], MOD-2);
        nwHash%=MOD;
        
        if(nwHash == Hash[N-i+1])
        {
            reverse(ALL(ns));
            for(int j=0;j<N-i+1;j++) ans.push_back(ns[j]);
            return ans;
        }
    }
    
    return ans;
}
 
int main()
{
    FIO;
    
    pw[0]=1;
    for(int i=1;i<MAX;i++) pw[i] = pw[i-1]*bas, pw[i]%=MOD;
    
    ll t;
    cin >> t;
    
    while(t--)
    {
        string s;
        cin >> s;
        
        ll n = s.size();
        
        for(int i=0;i<n;i++)
            Hash[i+1] = Hash[i] + ((s[i]-'a'+1)*pw[i])%MOD, Hash[i+1]%=MOD;
        
        reverse(ALL(s));
        
        for(int i=0;i<n;i++)
            rHash[i+1] = rHash[i] + ((s[i]-'a'+1)*pw[i])%MOD, rHash[i+1]%=MOD;
        
        ll inx = -1;
        for(int i=1;i<=n;i++)
            if(Hash[i] == rHash[i]) inx=i-1;
        
        ll bk = n-inx-1;
        
        if(inx==-1) bk=n;
        
        string ns;
        
        reverse(ALL(s));
        
        for(int i=inx+1;i<bk;i++) ns.push_back(s[i]);
        
        string tmp= Find(ns);
        reverse(ALL(ns));
        string bac= Find(ns);
        
        reverse(ALL(ns));
        
        ll rem[s.size()]={0};
        
        string fine;
        for(int i=0;i<=inx;i++) fine.push_back(s[i]), rem[i]=1;
        fine+=(tmp.size()>bac.size())?tmp:bac;
        for(int i=bk;i<n;i++) if(!rem[i])fine.push_back(s[i]);
        
        cout << fine << endl;
    }
    
    return 0;
}

ll MUL(ll x, ll y){return (x%MOD * y%MOD)%MOD;}
 
ll fastpow(ll a, ll p)
{
    if(p==0) return 1;
    ll mul= fastpow(a,p/2);
    
    if(p&1) return (MUL(MUL(mul,mul),a));
    return MUL(mul,mul);
}
 
ll ncr(ll n, ll r)
{
    ll ans=1;
    n--, r--;
    if(r > n-r) r=n-r;
    for(int i=1;i<=r;i++)
    {
        ans*=(n-i+1);        
        ans%=MOD;
        ans*= fastpow(i,MOD-2);
        ans%=MOD;
    }
    
    return ans;
}

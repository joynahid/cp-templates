#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MAX 100005

int L[MAX], P[MAX][20], T[MAX], D[MAX], n;
vector<pair<int,int>> g[MAX];

void dfs(int node, int par, int level, int cost)
{
	L[node]=level;
	T[node]=par;
	D[node]= cost;

	for(int i=0;i<g[node].size();i++)
	{
		if(g[node][i].first!=par)
		{
			dfs(g[node][i].first, node, level+1, cost+g[node][i].second);
		}
	}
}

void init()
{
	memset(P,-1,sizeof P);

	for(int i=0;i<n;i++) P[i][0]=T[i];

	for(int j=1; 1<<j <=n;j++)
		for(int i=0;i<n;i++)
			if(P[i][j-1]!=-1)
				P[i][j]= P[ P[i][j-1] ][j-1];
}

int lca(int u, int v)
{
	if(L[u]<L[v]) swap(u,v);

	int log;
	for(log=1; 1<<log <= L[u]; log++);
	log--;

	for(int i=log;i>=0;i--)
	{
		if(L[u]- (1<<i) >= L[v])
		{
			u=P[u][i];
		}
	}

	if(u==v)
	{
		return u;
	}

	for(int i=log;i>=0;i--)
	{
		if(P[u][i]!=-1 && P[u][i]!=P[v][i])
		{
			u= P[u][i];
			v= P[v][i];
		}
	}

	return T[u];
}

int kth(int u, int v, int k)
{
	int par= lca(u,v);

	if(L[u]-L[par]+1 >= k)
	{
		k= L[u]-k;
		k++;

		for(int i=log2(u);i>=0;i--)
		{
			if(L[u]- (1<<i) >= k)
				u=P[u][i];
		}

		return u+1;
	}
	else
	{
		k=  k-(L[u]-L[par])+L[par];
		k--;

		for(int i=19;i>=0;i--)
		{
			if(L[v]-(1<<i) >= k)
				v=P[v][i];
		}

		return v+1;
	}
}

int main()
{
	int t;
	char qu[10];;
	scanf("%d",&t);

	while(t--)
	{
		int q, root, u, v, k, c;
		scanf("%d",&n);

		for(int i=0;i<n-1;i++)
		{
			scanf("%d%d%d",&u,&v,&c);
			u--, v--;

			g[u].push_back({v,c});
			g[v].push_back({u,c});
		}

		dfs(0,-1,0, 0);
		init();

		while(1)
		{
			scanf("%s",qu);

			if(qu[1]=='O') break;

			scanf("%d%d",&u,&v);
			u--, v--;

			if(qu[0]=='D') printf("%d\n",D[u]+D[v]-2*D[lca(u,v)]);
			else
			{
				scanf("%d",&k);
				printf("%d\n",kth(u,v,k));
			}
		}

		for(int i=0;i<MAX;i++) g[i].clear();
	}

	return 0;
}

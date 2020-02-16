#include <bits/stdc++.h>
using namespace std;

#define MAX 50005

struct edge
{
    int u, v, w;
    bool operator<(const edge& p) const
    {
        return w < p.w;
    }
};

int par[MAX], node;
vector<edge> e;
vector<pair<int,int>> g[MAX];

int T[MAX], L[MAX], n;
int table[MAX][18], voot[MAX][18];
int D[MAX];

int find(int r) {return (par[r] == r) ? r : par[r]=find(par[r]);}

void mst()
{
    sort(e.begin(), e.end());

    for (int i = 0; i <=n; i++) par[i] = i;

    int count = 0;
    for (int i=0;i<(int)e.size();i++)
	{
        int u = find(e[i].u);
        int v = find(e[i].v);

        if (u != v)
		{
            par[u] = v;
            count++;

            g[e[i].u].push_back({e[i].v,e[i].w});
            g[e[i].v].push_back({e[i].u,e[i].w});

            if (count==n-1)
                break;
        }
    }
}

void dfs(int node, int par, int level, int cost)
{
	L[node]= level;
	T[node]= par;
	D[node]= cost;

	for(int i=0;i<g[node].size();i++)
	{
		if(g[node][i].first!=par)
		{
			dfs(g[node][i].first, node, level+1, g[node][i].second);
		}
	}
}

void query(int p, int q)
{
    int tmp, log, i;

    if (L[p] < L[q]) swap(p,q);

	for (log = 1; 1 << log <= L[p]; log++);
    log--;

    int ans=0;

    ///raising only 'p' to the level of 'q'
    for(i = log; i >= 0; i--)
        if (L[p] - (1 << i) >= L[q])
		{
			ans= max(voot[p][i],ans);
            p = table[p][i];
		}

    if(p == q)
	{
		printf("%d\n",ans);
        return;
	}

	///raising both node at the same time
    for(i = log; i >= 0; i--)
        if(table[p][i] != -1 && table[p][i] != table[q][i])
		{
			ans= max(voot[p][i],ans);
			ans= max(voot[q][i],ans);
            p = table[p][i], q = table[q][i];
		}

	printf("%d\n",max({ans, voot[p][0], voot[q][0]}));
	return;
}

void build()
{
    for(int i=0;i<MAX;i++)
		for(int j=0;j<18;j++)
			table[i][j]=-1;

    for(int i=0; i<n; i++)
    {
        table[i][0]= T[i];
        voot[i][0]= D[i];
    }

    for(int j=1; 1<<j <= n; j++)
    {
        for(int i=0; i<n; i++)
        {
            if(table[i][j-1] != -1)
            {
                table[i][j]=table[ table[i][j-1] ][j-1];
                voot[i][j]= max(voot[i][j-1],voot[ table[i][j-1] ][j-1]);
            }
        }
    }
}

int main()
{
	int t, cs=1;
	scanf("%d",&t);

	edge get;
	while(t--)
	{
		int m;
		scanf("%d%d",&n,&m);

		for (int i = 1; i <= m; i++)
		{
			int u, v, w;
			scanf("%d%d%d",&u,&v,&w);
			u--, v--;

			get.u = u;
			get.v = v;
			get.w = w;

			e.push_back(get);
		}

		mst();
		dfs(0,-1,0,0);
		build();

		int q;
		scanf("%d",&q);

		printf("Case %d:\n",cs++);
		while(q--)
		{
			int u, v;
			scanf("%d%d",&u,&v);
			u--, v--;

			query(u,v);
		}

		e.clear();
		for(int i=0;i<n;i++) g[i].clear();
		memset(T,0,sizeof T);
		memset(D,0,sizeof D);
		memset(L,0,sizeof L);
	}

    return 0;
}

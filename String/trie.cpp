//Find number of prefixes of all strings added

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MAX 2000005

int trie[MAX][26];
int cnt[MAX];
int en[MAX];

int node=1;

void insert(string &str)
{
	int nw=0;
	for(int j=0;j<str.size();j++)
	{
		int y= str[j]-'a';
		int &x=trie[nw][y];

		if(x==0)
		{
			x=node; //creates new node
			node++; //increment for further use
		}
		
		nw=x; //change 'nw' for further use
		
		cnt[x]++; //count occurences
		if(j+1==str.size()) en[x]=1; //endmark
	}
}

ll query(string &str)
{
	int nw=0, ans=INT_MAX;
	for(int j=0;j<str.size();j++)
	{
		int y= str[j]-'a';
		int &x=trie[nw][y];
		nw=x;
		
		ans=min(ans,cnt[nw]);
		
		if(x==0) break;
	}
	
	return ans;
}

void clrtrie()
{
	memset(trie,0,sizeof trie);
	memset(en,0,sizeof en);
	memset(cnt,0,sizeof cnt);
}

int main()
{
	ll t;
	scanf("%lld",&t);
	
	string op, word;
	
	while(t--)
	{
		cin >> op >> word;
		
		if(op=="add") insert(word);
		else printf("%lld\n",query(word));
	}
 
	return 0;
}

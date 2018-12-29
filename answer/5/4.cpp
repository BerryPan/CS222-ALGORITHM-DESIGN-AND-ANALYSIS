#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;

#define mm(a) memset((a),0,sizeof((a)))
#define INF 0xFFFFFF
#define MAXN 5000

struct node
{
	int to, c;
	int next;
}e[9999999];

int n, m, en, dis[MAXN], gap[MAXN];
int s, t;
int g[MAXN];
int matrix[210][210];
int que[MAXN];
bool deleted[MAXN / 2];

void add(int a, int b, int c)
{
	e[en].to = b;
	e[en].c = c;
	e[en].next = g[a];
	g[a] = en++;
	e[en].to = a;
	e[en].c = 0;
	e[en].next = g[b];
	g[b] = en++;
}

int sap(int u, int flow)
{
	if (u == t) return flow;
	int ans = 0, i, t;
	for (i = g[u]; i != -1; i = e[i].next)
	{
		if (e[i].c && dis[u] == dis[e[i].to] + 1)
		{
			t = sap(e[i].to, min(flow - ans, e[i].c));
			e[i].c -= t, e[i ^ 1].c += t, ans += t;
			if (ans == flow) return ans;
		}
	}
	if (dis[s] >= n * 2) return ans;
	if (!--gap[dis[u]]) dis[s] = n * 2;
	++gap[++dis[u]];
	return ans;
}

void build()
{
	en = 0;
	memset(g, -1, sizeof(g));
	for (int i = 1; i <= n; i++)
		if (i != s && i != t && !deleted[i]) add(i, i + n, 1);
	for (int i = 1; i <= n; i++)
	{
		if (i != s)
			if (matrix[s][i]) add(s, i, INF);
		if (i != t)
			if (matrix[t][i]) add(i + n, t + n, INF);
	}
	for (int i = 1; i <= n; i++)
	{
		if (i == s || i == t)	continue;
		for (int j = 1; j <= n; j++)
		{
			if (i == j) continue;
			if (matrix[i][j]) add(i + n, j, INF);

		}
	}
}


int main()
{
	cin >> n >> s >> t;
	int ans = 0, temp;
	memset(deleted, 0, sizeof(deleted));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin>>matrix[i][j];
	if (matrix[s][t] == 1)
	{
		cout << "NO ANSWER!" << endl;
	}
	build();
	mm(gap), mm(dis);
	t = t + n;
	for (gap[0] = n * 2; dis[s] < n * 2;)
		ans += sap(s, INF);
	cout << ans << " ";
	int t = 0, f = 0;
	for (int i = 1, j = ans; j; i++)
	{
		temp = j;
		j = 0;
		deleted[i] = true;
		t = t - n;
		build();
		mm(gap), mm(dis);
		t += n;
		for (gap[0] = n * 2; dis[s] < n * 2;)
			j += sap(s, INF);
		if (j < temp)
			que[t++] = i;
		else
			deleted[i] = false;
	}
	while (f < t)
	{
		cout<<que[f++]<<" ";
	}
	return 0;
}
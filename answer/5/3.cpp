#include <iostream>
#include <queue>
using namespace std;
#define MAXN 1100
#define INF 0xFFFFFF
struct node
{
	int u, v, c, f, next;  //C为花费，F为flow流量
}e[MAXN * 40];
int pre[MAXN], dis[MAXN], head[MAXN], t;
int vis[MAXN];
void add1(int u, int v, int c, int f)
{
	e[t].u = u;
	e[t].v = v;
	e[t].c = c;
	e[t].f = f;
	e[t].next = head[u];
	head[u] = t++;
}
void add(int u, int v, int c, int f)
{
	add1(u, v, c, f);
	add1(v, u, -c, 0);
}
int spfa(int s, int t)
{
	int i, u, v;
	queue<int>q;
	q.push(s);
	memset(vis, 0, sizeof(vis));
	memset(pre, -1, sizeof(pre));
	for (i = s; i <= t; i++)
		dis[i] = INF;
	dis[s] = 0;
	while (!q.empty())
	{
		u = q.front();
		q.pop();
		for (i = head[u]; i != -1; i = e[i].next)
		{
			v = e[i].v;
			if (e[i].f&&dis[v] > dis[u] + e[i].c)
			{
				dis[v] = dis[u] + e[i].c;
				pre[v] = i;
				if (!vis[v])
				{
					vis[v] = 1;
					q.push(v);
				}
			}
		}
		vis[u] = 0;
	}
	if (dis[t] != INF)
		return 1;
	return 0;
}
void solve(int s, int t)
{
	int ans = 0, i, j;
	int flow = 0, cost = 0;
	while (spfa(s, t))
	{
		int minf = INF;
		for (i = pre[t]; i != -1; i = pre[e[i].u])
		{
			if (e[i].f < minf)
				minf = e[i].f;
		}
		flow += minf;
		for (i = pre[t]; i != -1; i = pre[e[i].u])
		{
			j = i ^ 1;
			e[i].f -= minf;
			e[j].f += minf;
		}
		cost += dis[t] * minf;
	}
	cout << cost << endl;
}
int main()
{
	int i, u, v, c, n, m;
	cin >> n >> m;
	t = 0;
	memset(head, -1, sizeof(head));
	for (i = 0; i < m; i++)
	{
		cin >> u >> v >> c;
		add(u, v, c, 1);
		add(v, u, c, 1);
	}
	add(0, 1, 0, 2);
	add(n, n + 1, 0, 2);
	solve(0, n + 1);

	return 0;
}

#include <iostream>
#include<cstdio>
#include<cstring>
#define maxn 100000+10
using namespace std;
int cash, f[maxn], c[12], p[12];
int max(int a, int b)
{
	return a > b ? a : b;
}
void CompletePack(int cost)
{
	for (int i = cost; i <= cash; ++i)
		f[i] = max(f[i], f[i - cost] + cost);
}
void ZeroOnePack(int cost)
{
	for (int i = cash; i >= cost; --i)
		f[i] = max(f[i], f[i - cost] + cost);
}
void MultiplePack(int cost, int amount)
{
	if (cost*amount >= cash)
	{
		CompletePack(cost);
		return;
	}
	int k = 1;
	while (k < amount)
	{
		ZeroOnePack(k*cost);
		amount -= k;
		k = k * 2;
	}
	ZeroOnePack(amount*cost);
}
int main()
{
	int n;
	while (cin>>cash>>n)
	{	
		for (int i = 1; i <= n; ++i)
			cin >> c[i] >> p[i];;
		for (int i = 0; i <= cash; ++i)
			f[i] = 0;
		for (int i = 1; i <= n; ++i)
		{
			MultiplePack(p[i], c[i]);
		}
		cout << f[cash] << endl;
	}
	return 0;
}
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;
int b[200][200], p[200][200], num[200];

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n, minimum = 10000000, maximum = 0;
		cin>>n;
		for (int i = 0; i < n; i++)
		{
			cin >> num[i];
			for (int j = 0; j < num[i]; j++)
			{
				cin >> b[i][j] >> p[i][j];
				maximum = max(maximum, b[i][j]);
				minimum = min(minimum, b[i][j]);
			}
		}
		double ans = 0;
		for (int bw = minimum; bw <= maximum; bw++)
		{
			int sum = 0;
			for (int i = 0; i < n; i++)
			{
				int minp = 10000000;
				for (int j = 0; j < num[i]; j++)
				{
					if (b[i][j] >= bw && p[i][j] < minp)
						minp = p[i][j];
				}
				sum += minp;
			}
			if (bw / (sum * 1.0) > ans)
				ans = bw / (sum * 1.0);
		}
		cout << setprecision(3) << ans;
	}
}
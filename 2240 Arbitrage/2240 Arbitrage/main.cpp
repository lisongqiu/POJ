#include<cstdio>  
#include<cstring>  
#include<string>  
#include<map>  
using namespace std;
map<string, int> na;
const int N = 31;
double d[N], rate[N][N], r;
int n, m, ans;

int bellman(int s)
{
	memset(d, 0, sizeof(d));
	d[s] = 1.0;
	for (int k = 1; k <= n; ++k)
	{
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 1; j <= n; ++j)
				if (d[i] < d[j] * rate[j][i])
					d[i] = d[j] * rate[j][i];
		}
	}
	return d[s] > 1.0;
}

int main()
{
	int cas = 0;
	char s[100], a[100], b[100];
	while (scanf("%d", &n), n)
	{
		na.clear();
		ans = 0;
		memset(rate, 0, sizeof(rate));
		for (int i = 1; i <= n; ++i)
		{
			rate[i][i] = 1.0;
			scanf("%s", s);
			na[s] = i;
		}

		scanf("%d", &m);
		for (int i = 1; i <= m; ++i)
		{
			scanf("%s%lf%s", a, &r, b);
			rate[na[a]][na[b]] = r;
		}

		for (int i = 1; i <= n; ++i)
		{
			if (bellman(i))
			{
				ans = 1; break;
			}
		}
		printf("Case %d: %s\n", ++cas, ans ? "Yes" : "No");
	}
	return 0;
}
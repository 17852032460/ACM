#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>

using namespace std;

const int maxn = 20200;
const int mod = 1e9;

long long int a[maxn], dp[maxn][12], tree[maxn * 4];
int n, k, M;

long long int Query(int s, int t) //这里我用了zkw线段树，可能比树状数组慢点，但比普通线段树应该还是快不少的
{
	long long int ans = 0;
	for(s += M - 1, t += M + 1; s ^ t ^ 1; s >>= 1, t >>= 1)
	{
		if(~ s & 1)
			ans = (ans + tree[s ^ 1]) % mod;
		if(t & 1)
			ans = (ans + tree[t ^ 1]) % mod;
	}
	return ans % mod;
}

int main()
{
	//freopen("in.txt", "r", stdin);
	cin >> n >> k;
	memset(tree, 0, sizeof tree);
	for(int i = 1; i <= n; ++ i)
	{
		scanf("%lld", &a[i]);
		dp[i][1] = 1;
	}
	for(M = 1; M <= n + 1; M <<= 1);
	long long int ans = 0;
	for(int j = 2; j <= k; ++ j)
	{
		memset(tree, 0, sizeof tree);
		for(int i = 1; i <= n; ++ i)
		{
			dp[i][j] = Query(a[i], n);
			int cnt = ((M + a[i]) << 1);
			while(cnt >>= 1)
				tree[cnt] += dp[i][j - 1];
		}
	}
	for(int i = 1; i <= n; ++ i)
		ans = (ans + dp[i][k]) % mod;
	cout << ans << endl;
	return 0;
}

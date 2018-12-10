#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
 
using namespace std;
 
#define mem(a, i) memset(a, i, sizeof a)
 
const int maxn = 100100;
const int inf = 0x3f3f3f3f;
 
int ab(int x)
{
	return x > 0 ? x : -x;
}
 
class MCF
{
private:
	int n, s, t;
	int W[maxn], C[maxn], V[maxn];
	int head[maxn], next[maxn];
	int dis[maxn], prev[maxn], pree[maxn];
	bool vis[maxn];
	int cnt;
	int ans;
public:
	MCF(int nn, int ss, int tt) : n(nn), s(ss), t(tt)
	{
		cnt = -1;
		ans = 0;
		mem(head, 0xff);
		mem(next, 0xff);
	}
	void init(int nn, int ss, int tt)
	{
		n = nn;
		s = ss;
		t = tt;
	}
	void add(int u, int v, int w, int c)
	{
		cnt ++;
		V[cnt] = v;
		W[cnt] = w;
		C[cnt] = c;
		next[cnt] = head[u];
		head[u] = cnt;
	}
	void adde(int u, int v, int w, int c)
	{
		add(u, v, w, c);
		add(v, u, 0, -c);
	}
	bool spfa()
	{
		mem(vis, false);
		mem(prev, 0xff);
		mem(pree, 0xff);
		mem(dis, inf);
		queue <int> q;
		q.push(1);
		dis[1] = 0;
		while(!q.empty())
		{
			int now = q.front();
			q.pop();
			for(int i = head[now]; ~i; i = next[i])
			{
				if(W[i] > 0 && dis[V[i]] > dis[now] + C[i])
				{
					dis[V[i]] = dis[now] + C[i];
					prev[V[i]] = now;
					pree[V[i]] = i;
					if(!vis[V[i]])
					{
						vis[V[i]] = true;
						q.push(V[i]);
					}
				}
			}
			vis[now] = false;
		}
		if(dis[t] <= 100000)
		{
			return true;
		}
		return false;
	}
	int min_cost_flow()
	{
		while(spfa())
		{
			int x = t;
			int di = inf;
			while(x != s)
			{
				di = min(di, W[pree[x]]);
				x = prev[x];
			}
			x = t;
			while(x != s)
			{
				W[pree[x]] -= di;
				W[pree[x] ^ 1] += di;
				ans += di * C[pree[x]];
				x = prev[x];
			}
		}
		return ans;
	}
};
 
int main()
{
	char tu[110][110];
	int n, m;
	int mm, hh;
	pair <int, int> M[110], H[110];
	while(cin >> n >> m && (n || m))
	{
		MCF X(2 + 2 * mm, 1, 2 + 2 * mm);
		mm = 0;
		hh = 0;
		for(int i = 1; i <= n; ++ i)
		{
			for(int j = 1; j <= m; ++ j)
			{
				cin >> tu[i][j];
				if(tu[i][j] == 'm')
				{
					M[++ mm].first = i;
					M[mm].second = j;
				}
				if(tu[i][j] == 'H')
				{
					H[++ hh].first = i;
					H[hh].second = j;
				}
			}
		}
		X.init(2 + 2 * mm, 1, 2 + 2 * mm);
		for(int i = 1; i <= mm; ++ i)
		{
			for(int j = 1; j <= hh; ++ j)
			{
				X.adde(1 + i, 1 + mm + j, 1, ab(M[i].first - H[j].first) + ab(M[i].second - H[j].second));
			}
		}
		for(int i = 1; i <= mm; ++ i)
		{
			X.adde(1, 1 + i, 1, 0);
			X.adde(1 + mm + i, 2 + 2 * mm, 1, 0);
		}
		cout << X.min_cost_flow() << endl;
	}
	return 0;
}
 

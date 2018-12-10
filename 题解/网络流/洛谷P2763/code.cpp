#include <iostream>
#include <cstring>
#include <queue>
 
using namespace std;
 
#define mem(a, i) memset(a, i, sizeof a)
 
const int maxn = 30030;
const int inf = 0x3f3f3f3f;
 
class Dinic
{
private:
    int ans, cnt;
    int n, s, t;
    int type, maxk;
    int head[maxn], next[maxn];
    int W[maxn], V[maxn];
    int depth[maxn], cur[maxn];
    
    void init(int kk, int nn);
    void add(int u, int v, int w);
    bool bfs();
    int dfs(int u, int dist);
    void dinic();
    void show();
 
public:
    Dinic(int kk, int nn);
    ~Dinic();
};
 
Dinic::Dinic(int kk, int nn) : n(kk + nn + 2), t(kk + nn + 1), type(kk)
{
    s = 0;
    ans = 0;
    cnt = -1;
    maxk = 0;
    mem(head, 0xff);
    mem(next, 0xff);
 
    init(kk, nn);
    dinic();
}
 
Dinic::~Dinic()
{
    Dinic::show();
}
 
 
void Dinic::add(int u, int v, int w)
{
    cnt ++;
    W[cnt] = w;
    V[cnt] = v;
    next[cnt] = head[u];
    head[u] = cnt ++;
    W[cnt] = 0;
    V[cnt] = u;
    next[cnt] = head[v];
    head[v] = cnt;
}
 
void Dinic::init(int kk, int nn)
{
    int x;
    for(int i = 1; i <= kk; ++ i)
    {
        cin >> x;
        maxk += x;
        add(0, i, x);
    }
    int p;
    for(int i = 1; i <= nn; ++ i)
    {
        add(kk + i, t, 1);
        cin >> p;
        for(int j = 1; j <= p; ++ j)
        {
            cin >> x;
            add(x, kk + i, 1);
        }
    }
}
 
bool Dinic::bfs()
{
    mem(depth, 0);
    depth[s] = 1;
    queue <int> q;
    q.push(s);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int i = head[u]; ~i; i = next[i])
        {
            if(W[i] && !depth[V[i]])
            {
                depth[V[i]] = depth[u] + 1;
                if(V[i] == t)
                {
                    return true;
                }
                q.push(V[i]);
            }
        }
    }
    return false;
}
 
int Dinic::dfs(int u, int dist)
{
    if(u == t)
    {
        return dist;
    }
    int tmp = 0;
    for(int& i = cur[u]; ~i; i = next[i])
    {
        if(W[i] && depth[V[i]] == depth[u] + 1)
        {
            int di = dfs(V[i], min(W[i], dist));
            if(di)
            {
                W[i] -= di;
                W[i ^ 1] += di;
                tmp += di;        //优化二
                dist -= di;
                if(dist <= 0)
                {
                    break;
                }
            }
        }
    }
    return tmp;
}
 
void Dinic::dinic()
{
    while(bfs())       //优化一
    {
        for(int i = 0; i <= t; ++ i)
        {
            cur[i] = head[i];
        }
        while(int di = dfs(s, inf))       //优化三
        {
            ans += di;
        }
    }
}
 
void Dinic::show()
{
    if(ans == maxk)
    {
        for(int i = 1; i <= type; ++ i)
        {
            cout << i << ':';
            for(int j = head[i]; ~j; j = next[j])
            {
                if(!W[j] && V[j] > type)
                {
                    cout << ' ' << V[j] - type;
                }
            }
            cout << endl;
        }
    }
    else
    {
        cout << "No Solution!\n";
    }
}
 
int main()
{
    int k, n;
    cin >> k >> n;
    Dinic(k, n);
    return 0;
}

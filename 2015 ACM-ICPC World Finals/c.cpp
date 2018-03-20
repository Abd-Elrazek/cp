#include <bits/stdc++.h>

using namespace std;

/** Max Flow Min Cost **/
/* complexity : O(min(E^2 V log V, E log V F)) */
const int maxnodes = 2010;
const int INF = 1e9;
typedef long long ll;


int nodes = maxnodes;
int prio[maxnodes], curflow[maxnodes], prevedge[maxnodes], prevnode[maxnodes], q[maxnodes], pot[maxnodes];
bool inqueue[maxnodes];

struct Edge{
  int to, f, cap, cost, rev;
};

vector<Edge> graph[maxnodes];

void addEdge(int s, int t, int cap, int cost){
  Edge a = {t, 0, cap, cost, graph[t].size()};
  Edge b = {s, 0, 0, -cost, graph[s].size()};
  graph[s].push_back(a);
  graph[t].push_back(b);
}

void bellmanFord(int s, int dist[]){
  fill(dist, dist + nodes, INF);
  dist[s] = 0;
  int qt = 0;
  q[qt++] = s;
  for(int qh = 0; (qh - qt) % nodes != 0; qh++){
    int u = q[qh % nodes];
    inqueue[u] = false;
    for(int i = 0;i < (int) graph[u].size(); i++){
      Edge &e = graph[u][i];
      if(e.cap <= e.f) continue;
      int v = e.to;
      int ndist = dist[u] + e.cost;
      if(dist[v] > ndist){
        dist[v] = ndist;
        if(!inqueue[v]){
          inqueue[v] = true;
          q[qt++% nodes] = v;
        }
      }
    }
  }
}
pair<int,int> minCostFlow(int s, int t, int maxf){
  //bellmanFord can be safely commented if edges costs are non-negative
  bellmanFord(s, pot);
  int flow = 0;
  int flowCost = 0;
  while(flow < maxf){
    priority_queue<ll, vector<ll>, greater<ll> > q;
    q.push(s);
    fill(prio,prio + nodes, INF);
    prio[s] = 0;
    curflow[s] = INF;
    while(!q.empty()){
      ll cur = q.top();
      int d = cur >> 32;
      int u = cur;
      q.pop();
      if(d != prio[u]) continue;
      for(int i = 0;i < (int) graph[u].size(); i++){
        Edge &e = graph[u][i];
        int v = e.to;
        if(e.cap <= e.f) continue;
        int nprio = prio[u] + e.cost + pot[u] - pot[v];
        if(prio[v] > nprio){
          prio[v] = nprio;
          q.push(((ll) nprio << 32) + v);
          prevnode[v] = u;
          prevedge[v] = i;
          curflow[v] = min(curflow[u], e.cap - e.f);
        }
      }
    }

    if(prio[t] == INF) break;
    for(int i = 0;i < nodes; i++) pot[i] += prio[i];
      int df = min(curflow[t], maxf - flow);
    flow += df;
    for(int v = t; v != s; v = prevnode[v]){
      Edge &e = graph[prevnode[v]][prevedge[v]];
      e.f += df;
      graph[v][e.rev].f -= df;
      flowCost += df * e.cost;
    }
  }
  return make_pair(flow, flowCost);
}

/* usage example:
 * addEdge(source, target, capacity, cost)
 * minCostFlow(source, target, INF) -><flow,flowCost>
 */


int main() {
  int n, k;
  scanf("%d %d", &n, &k);
  int s = 2 * n+ 2, t = s+1;
  for (int i = 2; i <= n+1; ++i)
    addEdge(s, n+i, 1, 0);
  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      int cost = 0;
      scanf("%d", &cost);
      addEdge(j+n+2, i+1, 1, cost);
    }
  }
  addEdge(1, t, k, 0);
  for (int i = 2; i <= n; ++i)
    addEdge(i, t, 1, 0);
  pair<int, int> ans = minCostFlow(s, t, 1e9 + 7);
  printf("%d\n", ans.second);
  return 0;
}

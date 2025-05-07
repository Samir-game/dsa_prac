#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define edge pair<int, int>

class Graph
{
private:
  vector<pair<int, edge>> G; // graph
  vector<pair<int, edge>> T; // mst
  int *parent;
  int V; // number of vertices/nodes in graph
public:
  Graph(int V);
  void add_edge(int u, int v, int w);
  int find(int i);
  void uni(int u, int v);
  void kruskal();
  void print();
};

void Graph::add_edge(int u, int v, int w)
{
  G.push_back(make_pair(w, edge(u, v)));
}

Graph::Graph(int V)
{
  parent = new int[V];

  for (int i = 0; i < V; i++)
    parent[i] = i;
}
int Graph::find(int i)
{
  // If i is the parent of itself
  if (i == parent[i])
    return i;
  else
    return find(parent[i]);
}
void Graph::uni(int u, int v)
{
  parent[u] = v;
}

void Graph::kruskal()
{
  int i, u, v;
  sort(G.begin(), G.end()); // increasing weight
  for (i = 0; i < G.size(); i++)
  {
    u = find(G[i].second.first);
    v = find(G[i].second.second);
    if (u != v)
    {
      T.push_back(G[i]); // add to tree
      uni(u, v);
    }
  }
}
void Graph::print()
{
  cout << "Edge :"<< " Weight" << endl;
  int mincost=0;
  for (int i = 0; i < T.size(); i++)
  {
    cout << T[i].second.first << " - " << T[i].second.second << " : "
         << T[i].first;
    cout << endl;
    mincost+=T[i].first;
    
  }
  cout<<mincost<<endl;
}
int main()
{

  Graph g(7);

  g.add_edge(0, 1, 4);
  g.add_edge(0, 6, 10);
  g.add_edge(0, 2, 9);
  g.add_edge(1, 2, 8);
  g.add_edge(2, 3, 5);
  g.add_edge(2, 4, 2);
  g.add_edge(2, 6, 7);
  g.add_edge(3, 4, 3);
  g.add_edge(3, 5, 7);
  g.add_edge(4, 6, 6);
  g.add_edge(5, 6, 11);
  g.kruskal();
  g.print();
  return 0;
}
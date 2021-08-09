#include <bits/stdc++.h>

using namespace std;
using ll = pair<int, int>;

map<string, int> dicionario;
map<int, string> dic;

typedef struct Grafo
{
  int V;
  list <ll> *adj;
}grafo;

grafo *insercao_elementos(grafo *G);
grafo *reverso(grafo *G);
grafo *init(grafo *G, int n_vertices);

int main() {
  grafo *G;
  int n_vertices;

  cout << "Informe o número de elementos que tem o seu grafo\n";
  cin >> n_vertices;
  G = init(G, n_vertices);
  for(int i=0; i<G->V; i++)
  {
    string s;
    cin >> s;
    dicionario[s] = i;
    dic[i] = s;
  }

  G = insercao_elementos(G);


  for(int i=0; i<G->V; i++) {
    for(auto it : G->adj[i]){
        cout << dic[i] <<  ", " << dic[it.first] << endl;
    }
  }

  grafo *G_reverso;
  G_reverso = reverso(G);

  for(int i=0; i<G_reverso->V; i++) {
    for(auto it : G_reverso->adj[i]){
        cout << dic[i] <<  ", " << dic[it.first] << endl;
    }
  }

  return 0;
}

grafo *init(grafo *G, int n_vertices)
{
  G = (grafo*)malloc(sizeof(grafo));
  G->adj = new list<ll>[n_vertices];
  G->V = n_vertices;
  return G;
}

grafo *insercao_elementos(grafo *G)
{
  int count=0;
  while(1)
  {
    string origem, destino;
    cin >> origem >> destino;

    if(origem != "-1" && destino != "-1")
    {
      G->adj[dicionario[origem]].push_back(make_pair(dicionario[destino], 0));
      G->adj[dicionario[origem]].begin()->second++;
    }
    else
      break;
  }
  return G;
}

grafo *reverso(grafo *G)
{
  grafo *G_reverso;
  G_reverso = (grafo*)malloc(sizeof(grafo));
  G_reverso->V = G->V;
  G_reverso->adj = new list<ll>[G_reverso->V];

  for(int i=0; i<G->V; i++)
  {
    for(auto it : G->adj[i])
    {
      G_reverso->adj[it.first].push_back(make_pair(i, 0));
      G_reverso->adj[it.first].begin()->second++;
    }
  }

  return G_reverso;
}

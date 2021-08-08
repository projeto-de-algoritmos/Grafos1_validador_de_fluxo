#include <bits/stdc++.h>

using namespace std;
using ll = pair<int, int>;

typedef struct Grafo
{
  int V;
  list <ll> *adj;
}grafo;

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

  return 0;
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

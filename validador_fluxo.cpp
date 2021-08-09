#include <bits/stdc++.h>

using namespace std;
using ll = pair<int, int>;

map<string, int> dicionario;
map<int, string> dic;
priority_queue <pair<int, int>> heap;

typedef struct Grafo
{
  int V;
  list <ll> *adj;
}grafo;

grafo *insercao_elementos(grafo *G);
grafo *reverso(grafo *G);
grafo *init(grafo *G, int n_vertices);
grafo *excluir(grafo* G_reverso, int i);
grafo *BFS(grafo *G_reverso, int x);
pair<int, int> ordenacao_topologica(grafo *reverso);
void DFS(grafo *G, int origem); /*Busca em profundidade*/
vector<int> DFS_recursivo(grafo *G, int origem, vector<int> visitados); /*Busca em profundidade*/

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

  pair<int, int> flags; /*Flags são para pegar índices dos vértices "errados"*/
  flags = ordenacao_topologica(G_reverso);

  DFS(G, 0);
  DFS(G_reverso, 0);


  /*Se flags.first > 1, significa que existem nós que estão "errados"*/
  if(flags.first>-1)
  {
    cout << "Impossível montar esse fluxo!\n\n" << "Os cursos: " << dic[flags.first];
    cout << " e " << dic[flags.second] << " estão com pré-requisitos equivocados!\n";
    cout << "\nExiste um ciclo entre os seguintes componentes:\n\n";
  }

  else
    cout << "É possível montar esse fluxo !\n";

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

grafo *excluir(grafo* G_reverso, int i)
{
  for(int j=0; j<G_reverso->V; j++)
  {
    if(!G_reverso->adj[j].empty())
    for(list<ll> :: iterator it = G_reverso->adj[j].begin(); it != G_reverso->adj[j].end();it++)
    {
      if(it->first == i)
      {
        G_reverso->adj[j].erase(it);
        /*Atualizando o heap*/
        heap.push(make_pair(-(G_reverso->adj[j].begin()->second--), j));
        break;
      }
    }
  }
  return G_reverso;
}

pair<int, int> ordenacao_topologica(grafo *G_reverso)
{
  pair<int, int> flags;
  flags.first = -1;
  flags.second = -1;
  for(int i=0; i<G_reverso->V; i++)
  {
    heap.push(make_pair(-G_reverso->adj[i].begin()->second, i));
  }
  while(heap.top().first >= 0)
  {
    int j = heap.top().second;
    heap.pop();
    if(G_reverso->adj[j].empty())
      G_reverso = excluir(G_reverso, j);
  }

  for(int i=0; i<G_reverso->V; i++)
  {
    if(!G_reverso->adj[i].empty())
    {
      flags.first= i;
      flags.second = G_reverso->adj[i].begin()->first;
      break;
    }
  }

  return flags;
}

void DFS(grafo *G, int origem)
{
  cout << "\nDFS:\n";
  vector <int> visitados(G->V+2, 0);

  for(int i=origem; i<G->V; i++)
  {
    cout << "\nDFS:\n";
    vector <int> visitados(G->V+2, 0);

    for(int i=origem; i<G->V; i++)
    {
      if(visitados[i] == 0)
      {
        visitados[i] = 1;
        visitados = DFS_recursivo(G, i, visitados);
      }
    }

    for(int i=0; i<origem; i++)
    {
      if(visitados[i] == 0)
      {
        visitados[i] = 1;
        visitados = DFS_recursivo(G, i, visitados);
      }
    }

    cout << endl << endl;
  }

  vector<int> DFS_recursivo(grafo *G, int origem, vector <int> visitados)
  {
    cout << dic[origem] << " ";
    ++visitados[(G->V+1)]; // Para enumerar os nós pecorridos
    DFS_numering[origem].first = origem;
    for(auto it : G->adj[origem])
    {
      if(visitados[it.first] == 0)
      {
        visitados[it.first] = 1;
        visitados = DFS_recursivo(G, it.first, visitados);
      }
    }

    DFS_numering[origem].second = ++visitados[(G->V+1)];
    return visitados;
  }

grafo *BFS(grafo *G_reverso, int x)
{
  queue<int> fila;
  bool visitados[G_reverso->V];
  G_reverso = excluir(G_reverso, x);
  for(int i = 0; i < G_reverso->V; i++)
		visitados[i] = false;
  visitados[x] = true;
  while(true)
  {

    for(list<ll>::iterator it = G_reverso->adj[x].begin(); it != G_reverso->adj[x].end(); it++)
    {
      if(!visitados[it->first])
      {
        visitados[it->first] = true;
        fila.push(it->first);
      }
    }

    if(!fila.empty())
    {
      cout << dic[x] << " -> ";
      x = fila.front();
      fila.pop();
      G_reverso = excluir(G_reverso, x);
    }

    else
    {
      cout << dic[x] << "\n";
      break;
    }
  }

  return G_reverso;
}

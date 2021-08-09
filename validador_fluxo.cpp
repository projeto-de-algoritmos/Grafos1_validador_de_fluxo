/*
Alunos: Matheus Roberto e Daniel Oda

Para compilar: g++ trabalho_1.cpp -std=c++11
Para rodar testes: ./a.out < nome_do_teste.txt
*/

#include <bits/stdc++.h>

using namespace std;
using ll = pair<int, int>;

/*Variáveis globais*/
/*
DFS_numering.first = índice do elementos
DFS_numering.second = post do elemento
dic: int para string
dicionario: string para int
heap.first = n° de elementos do vértice
heap.second = índice do elemento
*/
vector<pair<int, int>> DFS_numering(50, make_pair(-1, -1));
map<string, int> dicionario;
map<int, string> dic;
priority_queue <pair<int, int>> heap;

/*Definindo estrutura do Grafo*/
typedef struct Grafo
{
  int V;
  list <ll> *adj;
  /*
  adj.first = índice da string
  adj.second = número de elementos
  */
}grafo;


/*Declarações das funções*/
grafo *init(grafo *G, int n_vertices); /*Função para inicializar grafos*/
grafo *insercao_elementos(grafo *G); /*Função para inserir elementos*/
grafo *reverso(grafo *G); /*Função para montar o grafo reverso*/
void DFS(grafo *G, int origem); /*Busca em profundidade*/
vector<int> DFS_recursivo(grafo *G, int origem, vector<int> visitados); /*Busca em profundidade*/
grafo *excluir(grafo* G_reverso, int i); /*Função para excluir o elemento i do grafo*/
void SCC(grafo *G_reverso); /*Função para entregar os elementos fortementes conectados*/
grafo *BFS(grafo *G_reverso, int x); /*Função busca em largura*/
bool comp(pair<int, int> a, pair<int, int> b);  /*Função de comparação para dar o sort*/
pair<int, int> ordenacao_topologica(grafo *reverso);

int main() {
  grafo *G;
  int n_vertices;

  //cout << "Informe o número de elementos que tem o seu grafo\n";
  cin >> n_vertices;
  G = init(G, n_vertices);
  for(int i=0; i<G->V; i++)
  {
    string s;
    cin >> s;
    /*Dois maps para facilitar o uso de string*/
    dicionario[s] = i;
    dic[i] = s;
  }

  G = insercao_elementos(G);

  grafo *G_reverso;
  G_reverso = reverso(G);

  pair<int, int> flags; /*Flags são para pegar índices dos vértices "errados"*/
  flags = ordenacao_topologica(G_reverso);

  /*Se flags.first > 1, significa que existem nós que estão "errados"*/
  if(flags.first>-1)
  {
    cout << "Impossível montar esse fluxo!\n\n" << "Os cursos: " << dic[flags.first];
    cout << " e " << dic[flags.second] << " estão com pré-requisitos equivocados!\n";
    cout << "\nExiste um ciclo entre os seguintes componentes:\n\n";
    SCC(G);
  }

  else
    cout << "É possível montar esse fluxo !\n";

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

/*
Função para verificar se existe ciclo no grafo
*/
pair<int, int> ordenacao_topologica(grafo *G_reverso)
{
  pair<int, int> flags;
  flags.first = -1;
  flags.second = -1;
  for(int i=0; i<G_reverso->V; i++)
  {
    // O valor é colocado como negativo para fazer a ordenação
    heap.push(make_pair(-G_reverso->adj[i].begin()->second, i));
  }

  /*Como o heap é atualizado, a contagem seria maior que o necessário*/
  // while(!heap.empty())

  /*Nem sempre é necessário visualizar todos os elementos, apenas os que tem a
  lista de adjacência igual a zero.*/
  //  for(int i=0; i<=G_reverso->V; i++)

  /*Enquanto existir elementos com 0 ou menos (pois está com sinal negativo)
  elementos no heap.*/
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

/*
Para encontrar grupo/os de elementos fortementes conectados
*/
void SCC(grafo *G_reverso)
{
  DFS(G_reverso, 0);
  G_reverso = reverso(G_reverso);
  sort(DFS_numering.begin(), DFS_numering.end(), comp);


  int j=0;
  for(int i=0; j!=-1; i++)
  {
    j = DFS_numering[i].first;
    if(j==-1) break;
    else if(!G_reverso->adj[j].empty())
    {
      /*Dentro do BFS já é realizada e exclusão*/
      G_reverso = BFS(G_reverso, j);
      cout << endl;
    }
    else
    G_reverso = excluir(G_reverso, j);
  }
}

/*
Função que exclui o nó com índice i de todas as listas de adjacências que ele se
encontra, é utilizado para fazer a ordenação topológica.
*/
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




/*
Busca em profundidade, necessária para fazer os elementos fortementes conectados
*/
void DFS(grafo *G, int origem)
{
  //cout << "\nDFS:\n";
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

  //cout << endl << endl;
}

vector<int> DFS_recursivo(grafo *G, int origem, vector <int> visitados)
{
//  cout << dic[origem] << " ";
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



/*
Busca em largura, necessária para verificar os grupos de elementos fortementes
conectados
*/
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


grafo *init(grafo *G, int n_vertices)
{
  G = (grafo*)malloc(sizeof(grafo));
  G->adj = new list<ll>[n_vertices];
  G->V = n_vertices;
  return G;
}

bool comp(pair<int, int> a, pair<int, int> b)
{
  return a.second > b.second; /*Retorna elemento com o maior segundo valor*/
}

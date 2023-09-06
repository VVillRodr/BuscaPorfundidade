#include <stdio.h>
#include <stdlib.h>

#define BRANCO 0
#define CINZA 1
#define PRETO 2
#define NIL -1

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct {
    int V;
    Node** adjList;
} GrafoA;

typedef struct {
    int cor;
    int pai;
    int tempoDescoberta;
    int tempoFinalizacao;
} DFS;

void DFS_Visit(GrafoA* G, int u, DFS* V, int* tempo) {

    V[u].cor = CINZA;

    (*tempo)+=1;

    V[u].tempoDescoberta = *tempo;

    Node* currentNode = G->adjList[u];
    while (currentNode != NULL) {
        int v = currentNode->value;
        if (V[v].cor == BRANCO) {
            V[v].pai = u;
            DFS_Visit(G, v, V, tempo);
        }
        currentNode = currentNode->next;
    }

    V[u].cor = PRETO;
    V[u].tempoFinalizacao = *tempo;
    (*tempo)+=1;

}

void Busca_Profundidade(GrafoA* G) {
    int u;
    DFS* V = (DFS*)malloc(G->V * sizeof(DFS));
    for (u = 0; u < G->V; u++) {
        V[u].cor = BRANCO;
        V[u].pai = NIL;
        V[u].tempoDescoberta = 0;
        V[u].tempoFinalizacao = 0;
    }

    int tempo = 0;
    for (u = 0; u < G->V; u++) {
        if (V[u].cor == BRANCO) {
            DFS_Visit(G, u, V, &tempo);
        }
    }

    for (u = 0; u < G->V; u++) {
        printf("Vertice %d: Descoberta: %d, Finalizacao: %d\n", u, V[u].tempoDescoberta, V[u].tempoFinalizacao);
    }

    free(V);
}

GrafoA* criarGrafo(int V) {
    GrafoA* grafo = (GrafoA*)malloc(sizeof(GrafoA));
    grafo->V = V;

    grafo->adjList = (Node**)malloc(V * sizeof(Node*));
    int i;
    for (i = 0; i < V; i++) {
        grafo->adjList[i] = NULL;
    }

    return grafo;
}

void adicionarAresta(GrafoA* grafo, int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = v;
    newNode->next = grafo->adjList[u];
    grafo->adjList[u] = newNode;
}

int main() {
    int V = 7;
    GrafoA* Ga = criarGrafo(14);

    adicionarAresta(Ga, 0, 3);
   adicionarAresta(Ga, 0, 1);
   adicionarAresta(Ga, 1, 2);
   adicionarAresta(Ga, 2, 5);
   adicionarAresta(Ga, 5, 6);
   adicionarAresta(Ga, 5, 4);
   adicionarAresta(Ga, 4, 1);
   adicionarAresta(Ga, 6, 4);
   adicionarAresta(Ga, 6, 3);
   adicionarAresta(Ga, 6, 0);
   adicionarAresta(Ga, 7, 8);
   adicionarAresta(Ga, 9, 10);
   adicionarAresta(Ga, 10, 11);
   adicionarAresta(Ga, 11, 9);

    Busca_Profundidade(Ga);

    return 0;
}

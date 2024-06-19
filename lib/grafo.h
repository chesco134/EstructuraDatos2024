#ifndef _GRAFO_H_
#include<stdlib.h>
#include"listas.h"

unsigned char compare_graph_nodes(void*, void*);

typedef struct GraphNode
{
	void* content;
	struct GraphNode* other_nodes;
} GraphNode;

typedef struct GraphEdge
{
	GraphNode* x;
	GraphNode* y;
	void* value;
} GraphEdge;

typedef struct Graph
{
	Lista* vertices;
	Lista* bordes;
} Graph;

GraphNode* graph_node(void* content)
{
	GraphNode* gn = (GraphNode*) calloc(1, sizeof(GraphNode));
	gn->content = content;
	gn->other_nodes = NULL;
	return gn;
}

GraphEdge* graph_edge(GraphNode* x, GraphNode* y, void* value)
{
	GraphEdge* ge = (GraphEdge*) calloc(1, sizeof(GraphEdge));
	ge->x = x;
	ge->y = y;
	ge->value = value;
	return ge;
}

Graph* graph()
{
	Graph* g = (Graph*) calloc(1, sizeof(Graph));
	g->vertices = NULL;
	g->bordes = NULL;
	return g;
}

unsigned char busca_nodo(Graph* g, GraphNode* x)
{
	unsigned char encontrado = 0;
	unsigned char comp = 0;
	Lista* l = g->vertices;
	if(l)
	{
		int len = l->size;
		int mid = len/2;
		unsigned char even = len % 2 == 0;
		Elemento* e;
		GraphNode* gn = NULL;
		if(even)
		{
		
		}
		else
		{
			e = obtener_elemento(l, mid);
			gn = e->dato;
			comp = compare_graph_nodes(gn->content, x->content);
			printf("Comparando compadres... se obtuvo %d\n", comp);
		}
	}
	return encontrado;
}

unsigned char es_adyacente(Graph* g, GraphNode* x, GraphNode* y)
{
	unsigned char adyacente = 0;
	
	return adyacente;
}

GraphNode* vecinos(Graph* g, GraphNode* vertice)
{
	return NULL;
}

void agregar_vertice(Graph* g, GraphNode* vertice)
{

}

void remover_vertice(Graph* g, GraphNode* vertice)
{
	
}

void agregar_borde(Graph* g, GraphNode* x, GraphNode* y, void* value)
{

}

GraphEdge* quitar_borde(Graph* g, GraphNode* x, GraphNode* y)
{
	return NULL;
}

void* obtener_valor_de_vertice(Graph* g, GraphNode* x)
{
	return NULL;
}

void colocar_valor_de_vertice(Graph* g, GraphNode* x, void* content)
{

}



#endif

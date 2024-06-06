#ifndef TREE_
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"listas.h"
#include"map.h"
#define max(a,b) ((a)>(b)?(a):(b))

typedef struct Nodo
{
	void* dato;
	struct Nodo* izquierda;
	struct Nodo* derecha;
} Nodo;

Nodo* crear_nodo(int dato)
{
	int* d = (int*)calloc(1, sizeof(int));
	*d = dato;
	Nodo* n = (Nodo*) calloc(1, sizeof(Nodo));
	n->dato = d;
	n->izquierda = NULL;
	n->derecha = NULL;
	return n;
}

void check_codes(Nodo* nodo, char* seq, int seq_size, Map* m) // Preorder
{
	if(!nodo->izquierda && !nodo->derecha)
	{
		CaracterFrecuencia* cf = (CaracterFrecuencia*)nodo->dato;
		char* cs = calloc(1, sizeof(char));
		cs[0] = cf->c;
		char* nseq = (char*) calloc(seq_size, sizeof(char));
		int i;
		for(i = 0; i<seq_size; i++)
		{
			nseq[i] = seq[i];
		}
		add(m, entry(cs, nseq));
		// printf("%s --> %c - %d\n", seq, cf->c, cf->freq);
	}
	else
	{
		int ln = seq_size + 1;
		int i;
		char* nseq = (char*) calloc(ln, sizeof(char));
		if(nodo->izquierda)
		{
			for(i=0; i<seq_size; i++)
			{
				nseq[i] = seq[i];
			}
			nseq[ln - 1] = '0';
			check_codes(nodo->izquierda, nseq, ln, m);
		}
		if(nodo->derecha)
		{
			for(i=0; i<seq_size; i++)
			{
				nseq[i] = seq[i];
			}
			nseq[ln - 1] = '1';
			check_codes(nodo->derecha, nseq, ln, m);
		}
	}
}

void preorder_cf(Nodo* nodo, int zero, int one)
{
	if(nodo)
	{
		CaracterFrecuencia* cf = (CaracterFrecuencia*) nodo->dato;
		if(zero == 1)
		{
			printf("0");
		}
		else if(one == 1)
		{
			printf("1");
		}
		printf("\t%c - %d\n", cf->c, cf->freq);
		preorder_cf(nodo->izquierda, 1, 0);
		preorder_cf(nodo->derecha, 0, 1);
	}
}

void inorder_cf(Nodo* nodo, int zero, int one)
{
	if(nodo)
	{
		CaracterFrecuencia* cf = (CaracterFrecuencia*) nodo->dato;
		if(zero == 1)
		{
			printf("0");
		}
		else if(one == 1)
		{
			printf("1");
		}
		inorder_cf(nodo->izquierda, 1, 0);
		printf("\t%c - %d\n", cf->c, cf->freq);
		inorder_cf(nodo->derecha, 0, 1);
	}
}

void postorder_cf(Nodo* nodo, int zero, int one)
{
	if(nodo)
	{
		CaracterFrecuencia* cf = (CaracterFrecuencia*) nodo->dato;
		if(zero == 1)
		{
			printf("0");
		}
		else if(one == 1)
		{
			printf("1");
		}
		postorder_cf(nodo->izquierda, 1, 0);
		postorder_cf(nodo->derecha, 0, 1);
		printf("\t%c - %d\n", cf->c, cf->freq);
	}
}

void preorder(Nodo* nodo)
{
	if(nodo)
	{
		printf("\t%d\n", *((int*)nodo->dato));
		preorder(nodo->izquierda);
		preorder(nodo->derecha);
	}
}

void inorder(Nodo* n)
{
	if(n)
	{
		inorder(n->izquierda);
		printf("\t%d\n", *((int*)n->dato));
		inorder(n->derecha);
	}
}

void postorder(Nodo* n)
{
	if(n)
	{
		postorder(n->izquierda);
		postorder(n->derecha);
		printf("\t%d\n", *((int*)n->dato));
	}
}

int altura(Nodo* arbol)
{
	if(!arbol)
	{
		return 0;
	}
	else
	{
		return max(altura(arbol->izquierda) + 1, altura(arbol->derecha) + 1);
	}
}

void mover_izquierda(Nodo** arbol)
{
	Nodo* padre;
	Nodo* mayor;
	padre = *arbol;
	mayor = (*arbol)->izquierda;
	while(mayor->derecha)
	{
		padre = mayor;
		mayor = mayor->derecha;
	}
	(*arbol)->dato = mayor->dato;
	if(padre == *arbol)
	{
		padre->izquierda = mayor->izquierda;
	}
	else
	{
		padre->derecha = mayor->izquierda;
	}
	*arbol = mayor;
}

void borrar(Nodo** arbol, int dato)
{
	Nodo* aux;
	if(!*arbol)
	{
		printf("No hay dato\n");
	}
	else
	{
		if(dato < *((int*)(*arbol)->dato))
		{
			borrar(&(*arbol)->izquierda, dato);
		}
		else if(dato > *((int*)(*arbol)->dato))
		{
			borrar(&(*arbol)->derecha, dato);
		}
		else
		{
			aux = *arbol;
			if(!aux->izquierda)
			{
				*arbol = aux->derecha;
			}
			else if(!aux->derecha)
			{
				*arbol = aux->izquierda;
			}
			else
			{
				mover_izquierda(&aux);
			}
			free(aux);
		}
	}
}

int compare_ints(void* a, void* b)
{
	int* x = (int*)a;
	int* y = (int*)b;
	return *x - *y;
}

Nodo* agregar_nodo(Nodo* arbol, int dato)
{
	Nodo* n = crear_nodo(dato);
	if(!arbol)
	{
		return n;
	}
	else
	{
		Nodo* aux = arbol;
		int cmp;
		while(aux)
		{
			cmp = compare_ints(aux->dato, n->dato);
			if(cmp < 0)
			{
				if(!aux->derecha)
				{
					aux->derecha = n;
					break;
				}
				else
				{
					aux = aux->derecha;
				}
			}
			else
			{
				if(!aux->izquierda)
				{
					aux->izquierda = n;
					break;
				}
				else
				{
					aux = aux->izquierda;
				}
			}
		}
	}
	return arbol;
}

#endif

#include<stdio.h>
#include<stdlib.h>
#include"lib/jcc.h"
#include"lib/help.h"

Nodo* nodo();
Nodo* arbol_agregar_nodo_huffman(Nodo*, Nodo*, int);
Lista* lista_nodos(Lista*);
Lista* arbolificacion(Lista*);
void imprime_lista_nodos(Lista*);
Lista* ordena(Lista*);
void ubica_elemento(Lista*, Elemento*);

// Escardar la lana.
int main(int argc, char** argv)
{
	if(argc > 1)
	{
		Map* m = map();
		Lista* lista;
		Lista* lista_de_listas;
	       	lista = leer_archivo(argv[1]);
		imprimir_lista_caracter_y_frecuencia(lista);
		lista_de_listas = agrupacion_en_listas(lista);
		ordena_listas(lista_de_listas);
		lista = (Lista*)lista_de_listas->primero->dato;
		imprimir_lista_caracter_y_frecuencia(lista);
		Lista* lista_de_nodos = lista_nodos(lista);
		printf("\n*****************\n\n");
		Lista* nl;
		imprime_lista_nodos(lista_de_nodos);
		nl = arbolificacion(lista_de_nodos);
		printf("FIN %d--->%d\n", lista_de_nodos->size, nl->size);
		Nodo* arbol;
		int height;
	       	arbol = (Nodo*)nl->primero->dato;
		char* seq = NULL;
		check_codes(arbol, seq, 0, m);
		height = altura(arbol);
		printf("La altura del arbol es: %d\n", height);
		printit(m->set, m->size);
		printf("Before done... %d of size.\n", m->size);
		char* palabra = "AHEEE";
		Byte_Bucket* bucket = codeit(palabra, m);
		int i;
		for(i=0; i<bucket->length; i++)
		{
			printf("\tByte número %d/%d: %d\n", i+1, bucket->length, bucket->bytes[i]);
		}
		char* decoded = decodeit(bucket, arbol, strlen(palabra));
		printf("******** %s *********\n", decoded);
		int bytes_processed = fcodeit(argv[1], argv[2], m);
		printf("\n\t---->>>>%s\n", fdecodeit(argv[2], argv[3], arbol, bytes_processed));
	}
	else
	{
		printf("Es necesario especificar como primer argumento la ruta a un archivo de texto para realizar la agrupación por frecuencias y ordenar.\n");
	}
	return 0;
}

Lista* ordena(Lista* lista)
{

	Lista* lista_de_listas;
	lista_de_listas = agrupacion_en_listas(lista);
	ordena_listas_nodo(lista_de_listas);
	lista = (Lista*)lista_de_listas->primero->dato;
	imprime_lista_nodos(lista);
	return lista;
}

void imprime_lista_nodos(Lista* l)
{
	Nodo* n;
	CaracterFrecuencia* cf;
	Elemento* e = l->primero;
	printf("******* Printing list of nodes *******\n");
	while(e)
	{
		n = (Nodo*) e->dato;
		cf = (CaracterFrecuencia*) n->dato;
		printf("\t%c - %d\n", cf->c, cf->freq);
		e = e->siguiente;
	}
}

Lista* arbolificacion(Lista* lista_de_nodos)
{
	if(lista_de_nodos->size == 1)
	{
		return lista_de_nodos;
	}
	Elemento* e;
	Elemento* e1;
	Elemento* e2;
	Elemento* ne;
	Nodo* n1;
	Nodo* n2;
	Nodo* n;
	int foil = 1;
	while(lista_de_nodos->size > 1)
	{
		e1 = quitar_elemento(lista_de_nodos, 0);
		e2 = quitar_elemento(lista_de_nodos, 0);
		n1 = (Nodo*) e1->dato;
		n2 = (Nodo*) e2->dato;
		n = arbol_agregar_nodo_huffman(n1, n2, foil);
		ne = crear_elemento(n);
		ubica_elemento(lista_de_nodos, ne);
		imprime_lista_nodos(lista_de_nodos);
		foil++;
	}
	return lista_de_nodos;
}

void ubica_elemento(Lista* lista_de_nodos, Elemento* e)
{
	Nodo* en = (Nodo*) e->dato;
	CaracterFrecuencia* ecf = (CaracterFrecuencia*) en->dato;
	Nodo* n;
	CaracterFrecuencia* cf;
	Elemento* iter = lista_de_nodos->primero;
	int i = 0;
	while(iter)
	{
		n = (Nodo*) iter->dato;
		cf = (CaracterFrecuencia*) n->dato;
		if(cf->freq > ecf->freq)
		{
			agregar_elemento(lista_de_nodos, e, i);
			return;
		}
		i++;
		iter = iter->siguiente;
	}
	agregar_elemento(lista_de_nodos, e, i);
}

Lista* lista_nodos(Lista* lista)
{
	CaracterFrecuencia* cf;
	Elemento* e = lista->primero;
	Lista* nl = crear_lista();
	Nodo* n;
	while(e)
	{
		cf = (CaracterFrecuencia*) e->dato;
		n = nodo();
		n->dato = cf;
		e->dato = n;
		agregar_elemento(nl, e, nl->size);
		e = e->siguiente;
	}
	return nl;
}

Nodo* arbol_agregar_nodo_huffman(Nodo* n1, Nodo* n2, int foil)
{
	CaracterFrecuencia* a = (CaracterFrecuencia*)n1->dato;
	CaracterFrecuencia* b = (CaracterFrecuencia*)n2->dato;
	int c = a->freq + b->freq;
	Nodo* n = nodo();
	CaracterFrecuencia* cf = crear_caracter_frecuencia('*', foil);
	cf->freq = c;
	if(a->freq > b->freq)
	{
		n->izquierda = n2;
		n->derecha = n1;
	}
	else
	{
		n->izquierda = n1;
		n->derecha = n2;
	}
	n->dato = cf;
	return n;
}

Nodo* nodo()
{
	Nodo* n = (Nodo*) calloc(1, sizeof(Nodo));
	n->dato = NULL;
	n->izquierda = NULL;
	n->derecha = NULL;
	return n;
}

void ordena_listas_nodo(Lista* lista_de_listas)
{
	Lista* sublista1 = NULL;
	Lista* sublista2 = NULL;
	Lista* lista_combinada = crear_lista();
	Elemento* e = NULL;
	Elemento* e1 = NULL;
	Elemento* e2 = NULL;
	Elemento* e3 = NULL;
	Nodo* n1 = NULL;
	Nodo* n2 = NULL;
	CaracterFrecuencia* cf1 = NULL;
	CaracterFrecuencia* cf2 = NULL;
	e = quitar_elemento(lista_de_listas, 0);
	int times = 0;
	while(lista_de_listas->size > 1 || (lista_de_listas->size >= 0 && e))
	{

		if(!sublista1)
		{
			sublista1 = (Lista*) e->dato;
			e = quitar_elemento(lista_de_listas, 0);
		}
		else if(!sublista2)
		{
			sublista2 = (Lista*) e->dato;
		}
		else
		{
			times++;
			printf("Times: %d\n", times);
			e1 = quitar_elemento(sublista1, 0);
			e2 = quitar_elemento(sublista2, 0);
			while(e1 && e2)
			{
				n1 = (Nodo*) e1->dato;
				n2 = (Nodo*) e2->dato;
				cf1 = (CaracterFrecuencia*) n1->dato;
				cf2 = (CaracterFrecuencia*) n2->dato;
				if(cf1->freq > cf2->freq)
				{
					e3 = crear_elemento(n2);
					agregar_elemento(lista_combinada, e3, lista_combinada->size);
					e2 = quitar_elemento(sublista2, 0);
				}
				else if(cf1->freq < cf2->freq)
				{
					e3 = crear_elemento(n1);
					agregar_elemento(lista_combinada, e3, lista_combinada->size);
					e1 = quitar_elemento(sublista1, 0);
				}
				else
				{
					if(cf1->prioridad > cf2->prioridad)
					{
						e3 = crear_elemento(n2);
						agregar_elemento(lista_combinada, e3, lista_combinada->size);
						e2 = quitar_elemento(sublista2, 0);
					}
					else
					{
						e3 = crear_elemento(n1);
						agregar_elemento(lista_combinada, e3, lista_combinada->size);
						e1 = quitar_elemento(sublista1, 0);
					}
					
				}
			}
			while(e1)
			{
				n1 = (Nodo*) e1->dato;
				cf1 = (CaracterFrecuencia*) n1->dato;
				e3 = crear_elemento(n1);
				agregar_elemento(lista_combinada, e3, lista_combinada->size);
				e1 = quitar_elemento(sublista1, 0);
			}
			while(e2)
			{
				n2 = (Nodo*) e2->dato;
				cf2 = (CaracterFrecuencia*) n2->dato;
				e3 = crear_elemento(n2);
				agregar_elemento(lista_combinada, e3, lista_combinada->size);
				e2 = quitar_elemento(sublista2, 0);
			}
			e3 = crear_elemento(lista_combinada);
			agregar_elemento(lista_de_listas, e3, lista_de_listas->size);
			lista_combinada = crear_lista();
			sublista1 = NULL;
			sublista2 = NULL;
			// imprime_lista_de_listas(lista_de_listas);
			e = quitar_elemento(lista_de_listas, 0);
		}
	}
	if(sublista1)
	{
		e3 = crear_elemento(sublista1);
		agregar_elemento(lista_de_listas, e3, lista_de_listas->size);
	}
}

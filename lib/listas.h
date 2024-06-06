#ifndef _LISTAS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct CaracterFrecuencia
{
	char c;
	int freq;
	int prioridad;
} CaracterFrecuencia;

typedef struct Elemento
{
	void* dato;
	struct Elemento* siguiente;
	struct Elemento* anterior;
} Elemento;

typedef struct Lista
{
	Elemento* primero;
	Elemento* ultimo;
	int size;
} Lista;

CaracterFrecuencia* crear_caracter_frecuencia(char, int);
Elemento* crear_elemento(void*);
Lista* crear_lista();
void agregar_elemento(Lista*, Elemento*, int);
Elemento* quitar_elemento(Lista*, int);
void agregar_caracter_y_frecuencia(Lista*, char, int);
void imprimir_lista_caracter_y_frecuencia(Lista*);
Lista* leer_archivo(char*);
Lista* agrupacion_en_listas(Lista*);
void imprime_lista_de_listas(Lista*);
void ordena_listas(Lista*);
void ordena_listas_nodo(Lista*);
Elemento* obtener_elemento(Lista*, int);

Elemento* obtener_elemento(Lista* lista, int pos)
{
	int mid = lista->size/2;
	int i;
	Elemento* iter = lista->primero;
	if(mid > pos)
	{
		for(i=0; i<mid; i++)
		{
			if(i == pos)
			{
				return iter;
			}
			iter = iter->siguiente;
		}
	}
	else
	{
		iter = lista->ultimo;
		for(i = lista->size - 1; i >= mid; i--)
		{
			if(i == pos)
			{
				return iter;
			}
			iter = iter->anterior;
		}
	}
	return NULL;
}

void ordena_listas(Lista* lista_de_listas)
{
	Lista* sublista1 = NULL;
	Lista* sublista2 = NULL;
	Lista* lista_combinada = crear_lista();
	Elemento* e = NULL;
	Elemento* e1 = NULL;
	Elemento* e2 = NULL;
	Elemento* e3 = NULL;
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
				cf1 = (CaracterFrecuencia*) e1->dato;
				cf2 = (CaracterFrecuencia*) e2->dato;
				if(cf1->freq > cf2->freq)
				{
					e3 = crear_elemento(cf2);
					agregar_elemento(lista_combinada, e3, lista_combinada->size);
					e2 = quitar_elemento(sublista2, 0);
				}
				else if(cf1->freq < cf2->freq)
				{
					e3 = crear_elemento(cf1);
					agregar_elemento(lista_combinada, e3, lista_combinada->size);
					e1 = quitar_elemento(sublista1, 0);
				}
				else
				{
					if(cf1->prioridad > cf2->prioridad)
					{
						e3 = crear_elemento(cf2);
						agregar_elemento(lista_combinada, e3, lista_combinada->size);
						e2 = quitar_elemento(sublista2, 0);
					}
					else
					{
						e3 = crear_elemento(cf1);
						agregar_elemento(lista_combinada, e3, lista_combinada->size);
						e1 = quitar_elemento(sublista1, 0);
					}
					
				}
			}
			while(e1)
			{
				cf1 = (CaracterFrecuencia*) e1->dato;
				e3 = crear_elemento(cf1);
				agregar_elemento(lista_combinada, e3, lista_combinada->size);
				e1 = quitar_elemento(sublista1, 0);
			}
			while(e2)
			{
				cf2 = (CaracterFrecuencia*) e2->dato;
				e3 = crear_elemento(cf2);
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

void imprime_lista_de_listas(Lista* lista_de_listas)
{
	Lista* sublista;
	Elemento* e;
	Elemento* e1;
	CaracterFrecuencia* cf;
	printf("Sublistas: %d\n", lista_de_listas->size);
	for(e = lista_de_listas->primero; e != NULL; e = e->siguiente)
	{
		sublista = (Lista*) e->dato;
		printf("\tElementos de sublista: %d\n", sublista->size);
		for(e1 = sublista->primero; e1 != NULL; e1 = e1->siguiente)
		{
			cf = (CaracterFrecuencia*) e1->dato;
			printf("\t\t%c - %d\n", cf->c, cf->freq);
		}
	}
}

Lista* agrupacion_en_listas(Lista* lista)
{
	Lista* lista_de_listas = crear_lista();
	if(lista)
	{
		Lista* lista_interna = crear_lista();
		Elemento* e;
		Elemento* ne;
		for(e = lista->primero; e != NULL; e = e->siguiente)
		{
			if(lista_interna->size == 1)
			{
				ne = crear_elemento(lista_interna);
				agregar_elemento(lista_de_listas, ne, lista_de_listas->size);
				lista_interna = crear_lista();
			}
			ne = crear_elemento(e->dato);
			agregar_elemento(lista_interna, ne, lista_interna->size);
		}
		if(lista_interna->size > 0)
		{
			ne = crear_elemento(lista_interna);
			agregar_elemento(lista_de_listas, ne, lista_de_listas->size);
		}
	}
	return lista_de_listas;
}

Elemento* quitar_elemento(Lista* lista, int pos)
{
	if(!lista || lista->size == 0)
		return NULL;
	if(pos == 0)
	{
		Elemento* aux = lista->primero;
		lista->primero = aux->siguiente;
		if(lista->size == 1)
		{
			lista->ultimo = lista->primero;
		}
		lista->size--;
		aux->siguiente = NULL;
		aux->anterior = NULL;
		return aux;
	}
	int mid = lista->size/2;
	int driver = mid - pos;
	int index = 0;
	Elemento* iter;
	if(driver > 0)
	{
		for(iter = lista->primero; iter != NULL; iter = iter->siguiente)
		{
			if(index == pos)
			{
				if(iter->siguiente)
				{
					iter->siguiente->anterior = iter->anterior;
				}
				if(iter->anterior)
				{
					iter->anterior->siguiente = iter->siguiente;
				}
				iter->siguiente = NULL;
				iter->anterior = NULL;
				lista->size--;
				return iter;
			}
			index++;
		}
	}
	else
	{
		index = lista->size - 1;
		for(iter = lista->ultimo; iter != NULL; iter = iter->anterior)
		{
			if(index == pos)
			{
				if(iter->siguiente)
				{
					iter->siguiente->anterior = iter->anterior;
				}
				if(iter->anterior)
				{
					iter->anterior->siguiente = iter->siguiente;
				}
				iter->anterior = NULL;
				iter->siguiente = NULL;
				lista->size--;
				return iter;
			}
			index--;
		}
	}
}

Lista* leer_archivo(char* file_path)
{
	Lista* lista = crear_lista();
	FILE* f = fopen(file_path, "r");
	int id = 0;
	if(f)
	{
		char* c = (char*) calloc(1, sizeof(char));
		int read = fread(c, sizeof(char), 1, f);
		CaracterFrecuencia* cf;
		while(read > 0)
		{
			agregar_caracter_y_frecuencia(lista, *c, id);
			read = fread(c, sizeof(char), 1, f);
			id++;
		}
		fclose(f);
	}
	else
	{
		printf("Error de archivo especificado, archivo probablemente no encontrado -->%s<--\n", file_path);
	}
	return lista;
}

void imprimir_lista_caracter_y_frecuencia(Lista* lista)
{
	Elemento* e;
	CaracterFrecuencia* cf;
	printf("Elementos de lista: %d\n", lista->size);
	for(e = lista->primero; e != NULL; e = e->siguiente)
	{
		cf = (CaracterFrecuencia*) e->dato;
		printf("%c - %d\n", cf->c, cf->freq);
	}
}

void agregar_caracter_y_frecuencia(Lista* lista, char c, int id)
{
//	if(c == '\n')
//		return;
	Elemento* e;
	CaracterFrecuencia* cf;
	for(e = lista->primero; e != NULL; e = e->siguiente)
	{
		cf = (CaracterFrecuencia*) e->dato;
		if(cf->c == c)
		{
			cf->freq++;
			return;
		}
	}
	cf = crear_caracter_frecuencia(c, id);
	e = crear_elemento(cf);
	agregar_elemento(lista, e, lista->size);
}

void agregar_elemento(Lista* lista, Elemento* e, int pos)
{
	if(lista)
	{
		Elemento* aux;
		if(lista->size == 0)
		{
			lista->primero = e;
			lista->ultimo = e;
			lista->size++;
		}
		else if(pos <= 0)
		{
			aux = lista->primero;
			lista->primero = e;
			e->siguiente = aux;
			aux->anterior = e;
			if(lista->size == 1)
			{
				lista->ultimo = aux;
			}
			lista->size++;
		}
		else if(pos > lista->size - 1)
		{
			aux = lista->ultimo;
			e->anterior = aux;
			aux->siguiente = e;
			lista->ultimo = e;
			lista->size++;
		}
		else
		{
			int mid = lista->size/2;
			int driver = mid - pos;
			int index = 0;
			if(driver > 0)
			{
				for(aux = lista->primero; aux != NULL; aux = aux->siguiente)
				{
					if(index == pos)
					{
						e->anterior = aux->anterior;
						if(aux->anterior)
						{
							aux->anterior->siguiente = e;
							aux->anterior = e;
						}
						e->siguiente = aux;
						lista->size++;
						return;
					}
					index++;
				}
			}
			else
			{
				index = lista->size - 1;
				for(aux = lista->ultimo; aux != NULL; aux = aux->anterior)
				{
					if(index == pos)
					{
						aux->anterior->siguiente = e;
						e->anterior = aux->anterior;
						aux->anterior = e;
						e->siguiente = aux;
						lista->size++;
						return;
					}
					index--;
				}
			}
		}
	}
}

Lista* crear_lista()
{
	Lista* lista = (Lista*) calloc(1, sizeof(Lista));
	lista->primero = NULL;
	lista->ultimo = NULL;
	lista->size = 0;
	return lista;
}

Elemento* crear_elemento(void* dato)
{
	Elemento* e = (Elemento*) calloc(1, sizeof(Elemento));
	e->dato = dato;
	e->siguiente = NULL;
	e->anterior = NULL;
	return e;
}

CaracterFrecuencia* crear_caracter_frecuencia(char c, int prioridad)
{
	CaracterFrecuencia* cf = (CaracterFrecuencia*)calloc(1, sizeof(CaracterFrecuencia));
	cf->c = c;
	cf->freq = 1;
	cf->prioridad = prioridad;
	return cf;
}
#endif

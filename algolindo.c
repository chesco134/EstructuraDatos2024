#include<stdio.h>
#include<stdlib.h>
#include"lib/listas.h"

int main(int argc, char** argv)
{
	if(argc > 1)
	{
		Lista* lista;
		Lista* lista_de_listas;
	       	lista = leer_archivo(argv[1]);
		imprimir_lista_caracter_y_frecuencia(lista);
		lista_de_listas = agrupacion_en_listas(lista);
		imprime_lista_de_listas(lista_de_listas);
		ordena_listas(lista_de_listas);
	}
	else
	{
		printf("Es necesario especificar como primer argumento la ruta a un archivo de texto para realizar la agrupación por frecuencias y ordenar.\n");
	}
	return 0;
}


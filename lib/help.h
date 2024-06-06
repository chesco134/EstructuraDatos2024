#ifndef _HELP
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct Byte_Bucket
{
	unsigned char* bytes;
	int length;
} Byte_Bucket;

void help();
void read_bytes_and_work();

int mn()
{
	unsigned char c = 0;
	c = ~c;
	unsigned char p = 1;
	unsigned char a = 1;
	a = ~a;
	printf("--->%d\n", a);
	while(p > 0)
	{
		p <<= 1;
		printf("\t%d\n", p);
	}
	while(c > 0)
	{
		c >>= 1;
		printf("%d\n", c);
	}
	return 0;
}
// Por cada caracter, hay un número decimal equivalente a su código binario, dicho código tiene una longitud (número de corrimientos), por cada byte, debes cuidar no empujar más allá del 8vo bit.

void help()
{
	// Obtener el código del caracter.
	// Obtener la longitud del código del caracter.
	// Obtener el total de corrimientos aceptables.
	// Efectuar los corrimientos aceptables.
	// Obtener la longitud del código que cabe.
	// Generar un número entero decimal equivalente a lo que cabe del código.
	// Hacer or con el byte activo actual.
	// Crear nuevo byte contenedor si es necesario.
	// Obtener el resto de corrimientos.
	// Generar un número entero decimal equivalente al resto del código.
	// Hacer or con el byte activo actual.	
}

Byte_Bucket* byte_bucket()
{
	Byte_Bucket* bb = (Byte_Bucket*) calloc(1, sizeof(Byte_Bucket));
	bb->bytes = (unsigned char*) calloc(1, sizeof(unsigned char));
	bb->length = 1;
	return bb;
}

int push(char* code)
{
	int a = 0;
	short m = 1;
	int i;
	for(i = 0; i<strlen(code); i++)
	{
		if(code[i] == '1')
		{
			a <<= 1;
			a |= m;
		}
		else
		{
			a <<= 1;
		}
	}
	printf("%s", code);
	// printf("Para %s = %d\n", code, a);
	return a;
}

int potencia_dos(int exponente)
{
	if(exponente == 0)
		return 1;
	int dos = 2;
	int i;
	for(i=0; i<exponente-1; i++)
	{
		dos *= 2;
	}
	return dos;
}

char* decodeit(Byte_Bucket* bucket, Nodo* arbolito, int chars)
{
	int current_byte = 0;
	int i;
	int j=0;
	unsigned char sensor;
	unsigned char current_bit = 7;
	unsigned char numeric_rep = 0;
	Nodo* nodo = arbolito;
	char* losesos = (char*) calloc(1, sizeof(char));
	unsigned char a = 0;
	while(current_byte <= bucket->length)
	{
		numeric_rep = potencia_dos(current_bit);
		sensor = numeric_rep & bucket->bytes[current_byte];
		if(sensor == numeric_rep)
		{
			a = 1;
		}
		else
		{
			a = 0;
		}
		printf("%d Current bit: %d, numeric_rep = %d, sensor: %d\n", a, current_bit, numeric_rep, sensor);
		if(sensor == numeric_rep)
		{
			// Vete pa la derecha
			if(!nodo->derecha)
			{
				printf("Ya no encontré camino, terminamos.\n");
				return losesos;
			}
			else
			{
				nodo = nodo->derecha;
			}
			// ¿Encontraste hoja?
			if(!nodo->izquierda && !nodo->derecha)
			{
				losesos[j] = ((CaracterFrecuencia*)nodo->dato)->c;
				j++;
				losesos = (char*) reallocarray(losesos, j, sizeof(char));
				printf("\t%s...\n", losesos);
				nodo = arbolito;
				chars--;
				if(chars == 0)
					break;
			}
		}
		else if(sensor == 0)
		{
			// Vete pa la izquierda, ¿Se puede?
			if(!nodo->izquierda)
			{
				printf("Ya no encontré camino, terminamos.\n");
				return losesos;
			}
			else
			{
				nodo = nodo->izquierda;
			}
			// ¿Encontraste hoja?
			if(!nodo->izquierda && !nodo->derecha)
			{
				losesos[j] = ((CaracterFrecuencia*)nodo->dato)->c;
				j++;
				losesos = (char*) reallocarray(losesos, j, sizeof(char));
				printf("\t%s...\n", losesos);
				nodo = arbolito;
				chars--;
				if(chars == 0)
					break;
			}
		}
		if(current_bit == 0)
		{
			current_bit = 8;
			current_byte++;
		}
		current_bit --;
	}
	printf("Terminandooo...\n");
	return losesos;
}

char* fdecodeit(char* filepath, char* out_filepath, Nodo* arbolito, int chars)
{
	if(!filepath)
	{
		return NULL;
	}
	if(!out_filepath)
	{
		return NULL;
	}
	int current_byte = 0;
	int i;
	int j=0;
	unsigned char sensor;
	unsigned char current_bit = 7;
	unsigned char numeric_rep = 0;
	Nodo* nodo = arbolito;
	char* losesos = (char*) calloc(1, sizeof(char));
	unsigned char a = 0;
	FILE* f = fopen(filepath, "r");
	if(!f)
		return NULL;
	unsigned char* uc = (unsigned char*) calloc(1, sizeof(unsigned char));
	int length = fread(uc, 1, sizeof(unsigned char), f);
	FILE* fo = fopen(out_filepath, "w");
	if(!fo)
	{
		return NULL;
	}
	while(length > 0)
	{
		numeric_rep = potencia_dos(current_bit);
		sensor = numeric_rep & *uc;
		if(sensor == numeric_rep)
		{
			a = 1;
		}
		else
		{
			a = 0;
		}
		printf("%d Current bit: %d, numeric_rep = %d, sensor: %d\n", a, current_bit, numeric_rep, sensor);
		if(sensor == numeric_rep)
		{
			// Vete pa la derecha
			if(!nodo->derecha)
			{
				printf("Ya no encontré camino, terminamos.\n");
				return losesos;
			}
			else
			{
				nodo = nodo->derecha;
			}
			// ¿Encontraste hoja?
			if(!nodo->izquierda && !nodo->derecha)
			{
				fwrite(&((CaracterFrecuencia*)nodo->dato)->c, 1, sizeof(char), fo);
//				losesos[j] = ((CaracterFrecuencia*)nodo->dato)->c;
//				j++;
//				losesos = (char*) reallocarray(losesos, j, sizeof(char));
//				printf("\t%s...\n", losesos);
				nodo = arbolito;
				chars--;
				if(chars == 0)
					break;
			}
		}
		else if(sensor == 0)
		{
			// Vete pa la izquierda, ¿Se puede?
			if(!nodo->izquierda)
			{
				printf("Ya no encontré camino, terminamos.\n");
				return losesos;
			}
			else
			{
				nodo = nodo->izquierda;
			}
			// ¿Encontraste hoja?
			if(!nodo->izquierda && !nodo->derecha)
			{
				fwrite(&((CaracterFrecuencia*)nodo->dato)->c, 1, sizeof(char), fo);
//				losesos[j] = ((CaracterFrecuencia*)nodo->dato)->c;
//				j++;
//				losesos = (char*) reallocarray(losesos, j, sizeof(char));
//				printf("\t%s...\n", losesos);
				nodo = arbolito;
				chars--;
				if(chars == 0)
					break;
			}
		}
		if(current_bit == 0)
		{
			current_bit = 8;
//			current_byte++;
			length = fread(uc, 1, sizeof(unsigned char), f);
		}
		current_bit --;
	}
	printf("Terminandooo...\n");
	return losesos;
}

int fcodeit(char* filepath, char* outfilepath, Map* m)
{
	
	int i;
	int j;
	int current_byte = 0;
	int bits_left = 8;
	int bits_que_caben;
	Byte_Bucket* bb = byte_bucket();
	char* lalenga;
	Entry* entry;
	int relg;
	int shift;
	int codelen;
	FILE* f = fopen(filepath, "r");
	FILE* of = fopen(outfilepath, "w");
	if(!f || !of)
		return 0;
	char* c = (char*) calloc(1, sizeof(char));
	int len = fread(c, 1, sizeof(char), f);
	int total = 0;
	int total_written = 0;
	char* str;
	while(len > 0)
	{
		total += len;
		str = (char*) calloc(1, sizeof(char));
		str[0] = *c;
		entry = get(m, str);
		if(entry)
		{
			codelen = strlen(entry->value);
			if(bits_left >= codelen)
			{
				bb->bytes[current_byte] <<= codelen;
				relg = push(entry->value);
				bb->bytes[current_byte] |= relg;
				bits_left -= codelen;
			}
			else
			{
				shift = 0;
				while(shift + bits_left < codelen)
				{
					bits_que_caben = bits_left;
					lalenga = (char*) calloc(bits_que_caben, sizeof(char));
					for(j = 0; j<bits_que_caben; j++)
					{
						lalenga[j] = ((char*)entry->value)[shift + j];
					}
					bb->bytes[current_byte] <<= bits_que_caben;
					relg = push(lalenga);
					bb->bytes[current_byte] |= relg;
					bb->bytes = (unsigned char*) reallocarray(bb->bytes, current_byte + 2, sizeof(unsigned char));
					bb->length++;
					current_byte++;
					shift += bits_que_caben;
					bits_left = 8;
				}
				lalenga = (char*) calloc(codelen - shift, sizeof(char));
				for(j=shift; j<codelen; j++)
				{
					lalenga[j-shift] = ((char*)entry->value)[j];
				}
				bb->bytes[current_byte] <<= codelen - shift;
				relg = push(lalenga);
				bb->bytes[current_byte] |= relg;
				bits_left -= codelen - shift;
			}
			if(bits_left == 0)
			{
				bb->bytes = (unsigned char*) reallocarray(bb->bytes, current_byte + 2, sizeof(unsigned char));
				bb->length++;
				current_byte++;
				bits_left = 8;
				if(bb->length % 100 == 0)
				{
					total_written = fwrite(bb->bytes, bb->length, sizeof(unsigned char), of);
					bb->bytes = (char*) calloc(1, sizeof(unsigned char));
					bb->length = 1;
					current_byte = 0;
				}
			}
		}
		else
		{
			printf("Pero que paja, no je encontró %s (i=%d)\n", str, i);
		}
		free(str);
		len = fread(c, 1, sizeof(char), f);
	}
	if(bits_left > 0)
	{
		bb->bytes[current_byte] <<= bits_left;
	}
	if(bb->length > 0)
	{
		total_written = fwrite(bb->bytes, bb->length, sizeof(unsigned char), of);
	}
	printf("\n\t%d - %d\n", total, total_written);
	fclose(f);
	fclose(of);
	return total;
}

Byte_Bucket* codeit(char* c, Map* m)
{
	int ln = strlen(c);
	printf("Working with %d chars: -->%s<--\n", ln, c);
	int i;
	int j;
	int current_byte = 0;
	int bits_left = 8;
	int bits_que_caben;
	Byte_Bucket* bb = byte_bucket();
	char* lalenga;
	char* str;
	Entry* entry;
	int relg;
	int shift;
	int codelen;
	for(i = 0; i<ln; i++)
	{
		str = (char*)calloc(1, sizeof(char));
		str[0] = c[i];
		entry = get(m, str);
		if(entry)
		{
			codelen = strlen(entry->value);
			if(bits_left >= codelen)
			{
				bb->bytes[current_byte] <<= codelen;
				relg = push(entry->value);
				bb->bytes[current_byte] |= relg;
				bits_left -= codelen;
			}
			else
			{
				shift = 0;
				while(shift + bits_left < codelen)
				{
					bits_que_caben = bits_left;
					lalenga = (char*) calloc(bits_que_caben, sizeof(char));
					for(j = 0; j<bits_que_caben; j++)
					{
						lalenga[j] = ((char*)entry->value)[shift + j];
					}
					bb->bytes[current_byte] <<= bits_que_caben;
					relg = push(lalenga);
					bb->bytes[current_byte] |= relg;
					bb->bytes = (unsigned char*) reallocarray(bb->bytes, current_byte + 2, sizeof(unsigned char));
					bb->length++;
					current_byte++;
					shift += bits_que_caben;
					bits_left = 8;
				}
				lalenga = (char*) calloc(codelen - shift, sizeof(char));
				for(j=shift; j<codelen; j++)
				{
					lalenga[j-shift] = ((char*)entry->value)[j];
				}
				bb->bytes[current_byte] <<= codelen - shift;
				relg = push(lalenga);
				bb->bytes[current_byte] |= relg;
				bits_left -= codelen - shift;
			}
//			printf("\tBits left: %d\n", bits_left);
			if(bits_left == 0)
			{
				bb->bytes = (unsigned char*) reallocarray(bb->bytes, current_byte + 2, sizeof(unsigned char));
				bb->length++;
				current_byte++;
				bits_left = 8;
			}
		}
		else
		{
//			printf("Pero que paja, no je encontró %c (i=%d)\n", c[i], i);
		}
		free(str);
	}
	if(bits_left > 0)
	{
		bb->bytes[current_byte] <<= bits_left;
	}
	printf("\n");
	return bb;
}

void ah(Nodo* n, char* seq, int seq_leng)
{
	if( !n->izquierda && !n->derecha )
	{
		printf("Imprime la seq... (y si quieres el caracter y su frecuencia)");
		return;
	}

	if(n->izquierda)
	{
		int nl = seq_leng + 1;
		char* nseq = (char*) calloc(nl, sizeof(char));
		int i;
		for(i = 0; i<seq_leng; i++)
		{
			nseq[i] = seq[i];
		}
		nseq[seq_leng] = '0';
		ah(n->izquierda, nseq, nl);
	}
	if(n->derecha)
	{
		
	}
}

#endif

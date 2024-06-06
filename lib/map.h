#ifndef _MAP_
#include<stdlib.h>
#include<string.h>
// #include"listas.h"

typedef struct Entry
{
	char* key;
	void* value;
} Entry;

typedef struct Map
{
	Entry* set;
	int size;
} Map;

Entry* entry(char* key, void* value)
{
	Entry* entry = (Entry*) calloc(1, sizeof(Entry));
	entry->key = key;
	entry->value = value;
	return entry;
}

Map* map()
{
	Map* map = (Map*) calloc(1, sizeof(Map));
	map->set = NULL;
	map->size = 0;
	return map;
}

Entry* locate_to_get(Entry* set, int min, int max, char* key)
{
	int size = max - min;
	int mid = size/2;
	short is_even = size % 2 == 0;
	short cmp;
	short cmp2;
	int i;
	Entry actual;
	Entry anterior;
	if(size == 1)
	{
		short cmp = strcmp(set[min].key, key);
		if(cmp == 0)
		{
			return &set[min];
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		cmp = strcmp(set[min].key, key);
		if(cmp == 0)
		{
			return &set[min];
		}
		else
		{
			cmp = strcmp(set[max-1].key, key);
			if(cmp == 0)
			{
				return &set[max-1];
			}
			else
			{
				if(is_even)
				{
					int mid_prev = min + mid - 1;
					cmp = strcmp(set[mid_prev].key, key);
					cmp2 = strcmp(set[min + mid].key, key);
					if(cmp == 0)
					{
						return &set[mid_prev];
					}
					else if(cmp2 == 0)
					{
						return &set[min + mid];
					}
					else if(cmp > 0)
					{
						// A la izquierda
						locate_to_get(set, min, mid_prev, key);
					}
					else if(cmp2 < 0)
					{
						// A la derecha
						locate_to_get(set, min + mid, max, key);
					}
					else
					{
						return NULL;
					}
				}
				else
				{
					cmp = strcmp(set[min + mid].key, key);
					if( cmp > 0 )
					{
						// A la izquierda
						locate_to_get(set, min, min + mid, key);
					}
					else if(cmp == 0)
					{
						return &set[min + mid];
					}
					else
					{
						// A la derecha
						locate_to_get(set, min + mid, max, key);
					}
				}
			}
		}
	}
}

Entry* get(Map* m, char* key)
{
	return locate_to_get(m->set, 0, m->size, key);
}

void reallocate(Entry* set, int size, int index, Entry* entry)
{
	Entry e;
	Entry prev_e;
	// printf("Working with: size = %d, index = %d\n", size, index);
	prev_e = set[index];
	set[index] = *entry;
	int i;
	for(i=index+1; i<size-1; i++)
	{
		e = set[i];
		set[i] = prev_e;
		prev_e = e;
	}
	set[size-1] = prev_e;
}

void printit(Entry* set, int size)
{
	int i;
	for(i = 0; i<size; i++)
	{
		printf("\t--->%s - %s\n", set[i].key, set[i].value);
	}
}

void locate(Entry* set, int min, int max, Entry* entry, int global_size)
{
	int size = max - min;
	int mid = size/2;
	short is_even = size % 2 == 0;
	short cmp;
	short cmp2;
	int i;
	Entry actual;
	Entry anterior;
	if(size == 1)
	{
		short cmp = strcmp(set[min].key, entry->key);
		if(cmp > 0)
		{
			reallocate(set, global_size, min, entry);
		}
		else
		{
			reallocate(set, global_size, min + 1, entry);
			printf("Element added at the end (%s - %s)\n", set[min + 1].key, set[min + 1].value);
		}
	}
	else
	{
		cmp = strcmp(set[min].key, entry->key);
		if(cmp > 0)
		{
			reallocate(set, global_size, min, entry);
		}
		else
		{
			cmp = strcmp(set[max-1].key, entry->key);
			if(cmp < 0)
			{
				reallocate(set, global_size, max, entry);
			}
			else
			{
				if(is_even)
				{
					int mid_prev = min + mid - 1;
					cmp = strcmp(set[mid_prev].key, entry->key);
					cmp2 = strcmp(set[min + mid].key, entry->key);
					if(cmp > 0 && cmp2 < 0)
					{
						reallocate(set, size + 1, min + mid, entry);
					}
					else if(cmp > 0)
					{
						// A la izquierda
						locate(set, min, mid_prev, entry, global_size);
					}
					else
					{
						// A la derecha
						locate(set, min + mid, max, entry, global_size);
					}
				}
				else
				{
					cmp = strcmp(set[min + mid].key, entry->key);
					if( cmp > 0 )
					{
						// A la izquierda
						locate(set, min, min + mid, entry, global_size);
					}
					else if(cmp == 0)
					{
						reallocate(set, size + 1, min + mid, entry);
					}
					else
					{
						// A la derecha
						locate(set, min + mid, max, entry, global_size);
					}
				}
			}
		}
	}
}

void add(Map* m, Entry* entry)
{
	if(m)
	{
		if(m->size == 0)
		{
			m->set = calloc(1, sizeof(Entry));
			m->set[0] = *entry;
		}
		else if(m->size == 1)
		{
			m->set = reallocarray(m->set, 2, sizeof(Entry));
			// printf("Memory reallocated for entry set.\n");
			short cmp = strcmp(m->set[0].key, entry->key);
			// printf("Compared %s vs %s, result is: %d\n", m->set[0].key, entry->key, cmp);
			if(cmp > 0)
			{
				m->set[1] = m->set[0];
				m->set[0] = *entry;
			}
			else
			{
				m->set[1] = *entry;
				// printf("Element added at the end (%s - %s)\n", m->set[1].key, m->set[1].value);
			}
		}
		else
		{
			m->set = reallocarray(m->set, m->size + 1, sizeof(Entry));
			Entry* set = m->set;
			int mid = m->size/2;
			short is_even = m->size % 2 == 0;
			short cmp = strcmp(set[0].key, entry->key);
			short cmp2;
			int i;
			Entry actual;
			Entry anterior;
			// printf("General case, compared against first element: %s vs %s (result: %d, is even? %d, size = %d)\n", set[0].key, entry->key, cmp, is_even, m->size);
			if(cmp > 0)
			{
				// printf("Came here (to when element is before first in list)\n");
				anterior = set[0];
				for(i=1; i<m->size; i++)
				{
					actual = set[i];
					set[i] = anterior;
					anterior = actual;
				}
				set[m->size] = anterior;
				set[0] = *entry;
				// printit(set, m->size + 1);
			}
			else
			{
				cmp = strcmp(set[m->size - 1].key, entry->key);
				// printf("Compared vs last: %s (last) vs %s (result %d)\n", set[m->size - 1].key, entry->key, cmp);
				if(cmp < 0)
				{
					set[m->size] = *entry;
				}
				else
				{
					if(is_even)
					{
						// printf("Came to when it is even...\n");
						int mid_prev = mid - 1;
						cmp = strcmp(set[mid_prev].key, entry->key);
						cmp2 = strcmp(set[mid].key, entry->key);
						// printf("Middle low: %s vs %s (%d), Middle high: %s vs %s (%d)\n", set[mid_prev].key, entry->key, cmp, set[mid].key, entry->key, cmp2);
						if(cmp < 0 && cmp2 > 0)
						{
							// printf("Mimihi\n");
							reallocate(set, m->size + 1, mid, entry);
						}
						else if(cmp > 0)
						{
							// A la izquierda
							// printf("Locating within first half...\n");
							locate(set, 0, mid_prev, entry, m->size + 1);
						}
						else
						{
							// A la derecha
							locate(set, mid, m->size, entry, m->size + 1);
						}
					}
					else
					{
						cmp = strcmp(set[mid].key, entry->key);
						if( cmp > 0 )
						{
							// A la izquierda
							locate(set, 0, mid, entry, m->size + 1);
						}
						else if(cmp == 0)
						{
							reallocate(set, m->size + 1, mid, entry);
						}
						else
						{
							// A la derecha
							locate(set, mid, m->size, entry, m->size + 1);
						}
					}
				}
			}
		}
	}
	m->size++;
}

#endif

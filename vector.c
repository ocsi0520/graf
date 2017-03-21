#include <stdlib.h>
#include <string.h>

#define _VECTOR_START(vec) ((void*)(vec)-sizeof(VECTOR_G))
#define _VECTOR_DATA(vec) ((void*)(vec)+sizeof(VECTOR_G))

typedef struct 
{
	unsigned _sizeof;
	unsigned _count; 
} VECTOR_G;

void* vector_create(int typesize)
{
	VECTOR_G* v = (VECTOR_G*) malloc(sizeof(VECTOR_G) + typesize);
	v->_sizeof = typesize;
	v->_count = 0;
	return _VECTOR_DATA(v);
}

void* vector_add(VECTOR_G* vector, void* item) 
{
	if(vector->_count == 0) 
		memcpy(_VECTOR_DATA(vector), item, vector->_sizeof);
	else 
	{
		vector = realloc(vector, sizeof(VECTOR_G) + (vector->_count+1) * vector->_sizeof);
		memcpy(_VECTOR_DATA(vector)+(vector->_count*vector->_sizeof), item, vector->_sizeof);
	}

	vector->_count++;
	return _VECTOR_DATA(vector);
}

#define VECTOR(type) ((type*)vector_create(sizeof(type)))
#define VECTOR_ADD(vector, item) (vector_add(_VECTOR_START(vector), &(item))) 
#define VECTOR_LENGTH(vector) (((VECTOR_G*)(_VECTOR_START(vector)))->_count)

#define VECTOR_EMPLACE(vector, type, value) { \
	type v = value; \
	vector = VECTOR_ADD(vector, v); \
} 

#include <stdio.h>

int main() 
{
	int* data = VECTOR(int);
	VECTOR_EMPLACE(data, int, 5);
	VECTOR_EMPLACE(data, int, 4);
	VECTOR_EMPLACE(data, int, 6);
	VECTOR_EMPLACE(data, int, 7);

	for(int i = 0; i < VECTOR_LENGTH(data); i++)
		printf("%d] %d\n", i, data[i]);
}
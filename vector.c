#include <stdlib.h>
#include <string.h>
#include "vector.h"

#ifdef HAVE_DEBUG
	#include <stdio.h>
	#define DEBUG(...) printf("[DEBUG] " __VA_ARGS__)
#else 
	#define DEBUG(...) 
#endif 

void* _vector_create(int typesize)
{
	unsigned _tmp_capacity=2;
	VECTOR_G* v = (VECTOR_G*) malloc(sizeof(VECTOR_G) + typesize*_tmp_capacity);
	v->_sizeof = typesize;
	v->_count = 0;
	v->_capacity=_tmp_capacity;
	return _VECTOR_DATA(v);
}

void* _vector_add(VECTOR_G* vector, void* item) 
{
	if(vector->_count < vector->_capacity)
		memcpy(_VECTOR_DATA(vector) + (vector->_sizeof*vector->_count) , item, vector->_sizeof);
	else 
	{
		vector->_capacity = (vector->_capacity*3)/2; // Parentheses not necessary, justin case (tm)

		vector = realloc(vector, sizeof(VECTOR_G) + vector->_capacity * vector->_sizeof);
		memcpy(_VECTOR_DATA(vector)+(vector->_count*vector->_sizeof), item, vector->_sizeof);
		
		DEBUG("újat foglaltam: capacity: %d, count: %d\n",vector->_capacity, vector->_count);
	}

	vector->_count++;
	return _VECTOR_DATA(vector);
}

void _vector_free(VECTOR_G* vector)
{
	free(vector);
}
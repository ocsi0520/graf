#include <stdlib.h>
#include <string.h>
#include "vector.h"

void* _vector_create(int typesize)
{
	VECTOR_G* v = (VECTOR_G*) malloc(sizeof(VECTOR_G) + typesize);
	v->_sizeof = typesize;
	v->_count = 0;
	return _VECTOR_DATA(v);
}

void* _vector_add(VECTOR_G* vector, void* item) 
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
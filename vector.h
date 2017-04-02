#pragma once

#define _VECTOR_START(vec) ((void*)(vec)-sizeof(VECTOR_G))
#define _VECTOR_DATA(vec) ((void*)(vec)+sizeof(VECTOR_G))

#define VECTOR(type) ((type*)_vector_create(sizeof(type)))
#define VECTOR_ADD(vector, item) (_vector_add(_VECTOR_START(vector), &(item))) 
#define VECTOR_LENGTH(vector) (((VECTOR_G*)(_VECTOR_START(vector)))->_count)

#define VECTOR_EMPLACE(vector, type, value) { \
	type v = value; \
	vector = VECTOR_ADD(vector, v); \
} 

#define VECTOR_FREE(v) _vector_free(_VECTOR_START(v))

//void*-ok tömbje
#define VECTOR_FREE_MULTIPLE(...) { \
void* _to_free[]={__VA_ARGS__}; \
int _length=sizeof(_to_free)/sizeof(_to_free[0]); \
int i; \
	for(i=0;i<_length;i++) \
 		free(_to_free[i]);	\
}


typedef struct 
{
	unsigned _sizeof;
	unsigned _count;
	unsigned _capacity;
} VECTOR_G;

void* _vector_create(int typesize);
void* _vector_add(VECTOR_G* vector, void* item);
void _vector_free(VECTOR_G* vector);
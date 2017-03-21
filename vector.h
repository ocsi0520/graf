
#define _VECTOR_START(vec) ((void*)(vec)-sizeof(VECTOR_G))
#define _VECTOR_DATA(vec) ((void*)(vec)+sizeof(VECTOR_G))

#define VECTOR(type) ((type*)_vector_create(sizeof(type)))
#define VECTOR_ADD(vector, item) (_vector_add(_VECTOR_START(vector), &(item))) 
#define VECTOR_LENGTH(vector) (((VECTOR_G*)(_VECTOR_START(vector)))->_count)

#define VECTOR_EMPLACE(vector, type, value) { \
	type v = value; \
	vector = VECTOR_ADD(vector, v); \
} 


typedef struct 
{
	unsigned _sizeof;
	unsigned _count; 
} VECTOR_G;

void* _vector_create(int typesize);
void* _vector_add(VECTOR_G* vector, void* item);
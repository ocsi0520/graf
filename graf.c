#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

#define talloc(type) (type*)malloc(sizeof(type))


typedef struct
{
	char* name;
}
NODE;

typedef struct 
{
	int from;
	int to;
}
RELATION;

typedef struct 
{
	NODE* nodes;
	RELATION* relations;

	char* _data;
	unsigned _size;
} GRAPH;

GRAPH* graph_create();
int graph_add_node(GRAPH* graph, NODE node);
int graph_add_relation(GRAPH* graph, RELATION rel);
GRAPH* graph_load(char* file_name);
void graph_write(GRAPH* graph);
void graph_destroy(GRAPH* graph);


GRAPH* graph_create()
{
	GRAPH* new_graph=talloc(GRAPH);//(GRAPH*)malloc(sizeof(GRAPH));
	new_graph->nodes=VECTOR(NODE);
	new_graph->relations=VECTOR(RELATION);

	new_graph->_data=NULL;
	new_graph->_size=0;

	return new_graph;
}


GRAPH* graph_load(char* file_name)
{
	FILE* fp=fopen(file_name,"r");
	if(!fp)
		return NULL;

	GRAPH* new_graph=graph_create();

	fseek(fp,0,SEEK_END);
	size_t size=ftell(fp);

	char* data=(char*) malloc(size);
	new_graph->_data=data;

	fseek(fp,0,SEEK_SET);
	fread(data,size,1,fp);

	fclose(fp);

	

	char* c=data;
	while(*c!='\0')
	{
		NODE A;
		A.name=c;
		c=strchr(c,' ');
		*c='\0';

		NODE B;
		B.name=++c;
		c=strchr(c,'\n');

		if(c==NULL)
		{
			RELATION re={graph_add_node(new_graph,A),graph_add_node(new_graph,B)};
			graph_add_relation(new_graph,re);
			break;
		}
		*c='\0';
		c++;

		RELATION re={graph_add_node(new_graph,A),graph_add_node(new_graph,B)};
		graph_add_relation(new_graph,re);
	}

	return new_graph;
}

int graph_add_node(GRAPH* graph, NODE node)
{
	for(int i = 0; i < VECTOR_LENGTH(graph->nodes); i++)
		if(!strcmp(graph->nodes[i].name, node.name))
			return i;

	graph->nodes = VECTOR_ADD(graph->nodes, node);


	return VECTOR_LENGTH(graph->nodes)-1;
}

int graph_add_relation(GRAPH* graph, RELATION rel)
{
	for(int i=0;i < VECTOR_LENGTH(graph->relations); i++)
	{
		if(rel.from == graph->relations[i].from && rel.to == graph->relations[i].to)
			return i;
	}

	graph->relations=VECTOR_ADD(graph->relations,rel);

	return VECTOR_LENGTH(graph->relations)-1;
}

void graph_write(GRAPH* graph)
{
	printf("nodes:\n");
	for(int i=0;i < VECTOR_LENGTH(graph->nodes); i++)
		printf("%s || ",graph->nodes[i].name);

	printf("relations:\n");
	for(int i=0;i < VECTOR_LENGTH(graph->relations); i++)
		printf("%d - %d || ",graph->relations[i].from,graph->relations[i].to);
}

void graph_destroy(GRAPH* graph)
{
	//free(_VECTOR_START(graph->nodes));
	//free(_VECTOR_START(graph->relations));
	VECTOR_FREE_MULTIPLE(graph->nodes,graph->relations);
	//VECTOR_FREE(graph->nodes);
	//VECTOR_FREE(graph->relations);
	free(graph->_data);
	free(graph);
}



void graph_perambulate(GRAPH * graph)
{	
	NODE* all=(NODE*) malloc(sizeof(NODE)*VECTOR_LENGTH(graph->nodes));
	
	NODE* black=(NODE*) malloc(sizeof(NODE)*VECTOR_LENGTH(graph->nodes));
}
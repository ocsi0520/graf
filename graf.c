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
	NODE* from;
	NODE* to;
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

GRAPH* load(char* file_name)
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

		printf("%s\t",A.name);

		graph_add_node(new_graph, A);

		NODE B;
		B.name=++c;
		c=strchr(c,'\n');
		if(c==NULL)
		{
			printf("%s\n",B.name);
			break;
		}
		*c='\0';
		printf("%s\n",B.name);
		c++;

		graph_add_node(new_graph, B);
		//printf("%s\t%s\n",A.name,B.name);
	}
	NODE n = {"asd"};

	return new_graph;
}

int graph_add_node(GRAPH* graph, NODE node)
{
	for(int i = 0; i < VECTOR_LENGTH(graph->nodes); i++)
		if(!strcmp(graph->nodes[i].name, node.name))
			return 0;

	graph->nodes = VECTOR_ADD(graph->nodes, node);


	return 1;
}

int main()
{
	if(!load("graf.txt"))
		printf("bazdmeg");
	return 0;
}
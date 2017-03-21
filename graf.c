#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
} GRAPH;


GRAPH* graph_create();
int graph_add_node(GRAPH* graph, NODE node);
int graph_add_relation(GRAPH* graph, RELATION rel);
void graph_destroy(GRAPH* graph);


GRAPH* graph_create()
{
	GRAPH* new_graph=talloc(GRAPH);//(GRAPH*)malloc(sizeof(GRAPH));
	new_graph->nodes=new_graph->relations=NULL;
	return new_graph;
}

GRAPH* load(char* file_name)
{
	FILE* fp=fopen(file_name,"r");
	if(!fp)
		return NULL;

	fseek(fp,0,SEEK_END);
	size_t size=ftell(fp);

	char* data=(char*) malloc(size);

	fseek(fp,0,SEEK_SET);
	fread(data,size,1,fp);

	fclose(fp);

	printf("Loaded %ld bytes from %s\n", size, file_name);

	GRAPH* new_graph=graph_create();
	/*for(char* c=data-1;c<data+size;*(c=strchr(c,'\n'))=0)
	{
		NODE A;A.name=++c;// + (c!=data);
		c=strchr(c,' ');
		*c='\0';

		c++;
		NODE B;B.name=c;
	}*/
	char* c=data;
	while(*c!='\0')
	{
		NODE A;
		A.name=c;
		c=strchr(c,' ');
		*c='\0';

		printf("%s\t",A.name);

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
		//printf("%s\t%s\n",A.name,B.name);
	}
	NODE n = {"asd"};

	return new_graph;
}

int graph_add_node(GRAPH* graph, NODE node)
{
	if(graph->nodes==NULL)
	{
		graph->nodes=(NODE*) malloc(sizeof(NODE)*64);
		graph->nodes[graph->count++]=node;
		return 1;
	}
	NODE* current;
	for(current=graph->nodes;;current++) //megnézzük h benne van-e
		if(!strcmp(current->name,node.name)) //ha bennevan nem rakjuk bele, fuck you ha kinevetsz Tomi a kommentjeim miatt :'(
			return 0;

	graph->nodes[graph->count++]=node;
	return 1;
}

int main()
{
	if(!load("graf.txt"))
		printf("bazdmeg");
	return 0;
}
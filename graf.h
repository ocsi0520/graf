#pragma once

typedef struct NODE NODE;
typedef struct RELATION RELATION; 
typedef struct GRAPH GRAPH;

GRAPH* graph_create();
int graph_add_node(GRAPH* graph, NODE node);
int graph_add_relation(GRAPH* graph, RELATION rel);
GRAPH* graph_load(char* file_name);
void graph_write(GRAPH* graph);
void graph_destroy(GRAPH* graph);
void graph_perambulate(GRAPH * graph);
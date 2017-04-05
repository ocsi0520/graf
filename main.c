#include <stdio.h>
#include "graf.h"

int main()
{
	GRAPH* asd;
	if(!(asd=graph_load("graf.txt")))
		printf("bazdmeg");
	graph_write(asd);

	graph_destroy(asd);
	return 0;
}
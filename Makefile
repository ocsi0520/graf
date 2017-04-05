default: graf

CFLAGS = -Ic-vector/
graf: graf.c c-vector/vector.c main.c

debug: CFLAGS += -DHAVE_DEBUG -ggdb
debug: graf 
	
clean: 
	rm graf
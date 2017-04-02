default: graf

graf: graf.c vector.c main.c

debug: graf 
debug: CFLAGS = -DHAVE_DEBUG
	
clean: 
	rm graf
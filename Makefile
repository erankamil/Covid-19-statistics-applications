CC = gcc
CORONA_LIB = Ex01utils

#BINS will hold an array of all the _*.c files that he changed to _*.out
BINS := $(subst .c,.out,$(shell find .  -name "_*.c"))

#BINS will hold an array of all the lib*.c that he changed to lib*.so files 
LIBS := $(subst .c,.so,$(shell find .  -name "lib*.c"))

all: $(LIBS)  $(BINS) 
	export LD_LIBRARY_PATH=$(shell pwd)
	
%.out: %.c 
	$(CC) $^ -L$(shell pwd) -l$(CORONA_LIB) -o $@ 

lib%.so : lib%.c 
	$(CC) -shared -fPIC $^ -o $@ 
	
clean:
	rm -vf *.out *.so

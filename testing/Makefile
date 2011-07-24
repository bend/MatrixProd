CFLAGS+=-W -Wall -lpthread -lgmp -Werror -std=c99 -pedantic -g
EXEC=matrixprod
SOURCES=$(wildcard *.c)
LIBS=$(filter-out ../main.c, $(wildcard ../*.c))
OBJECTS=$(SOURCES:.c=.o)
LDFLAGS+=-Lpthread -Lgmp
all: tests
debug: CFLAGS= -g -DDEBUG -lgmp -lpthread -std=c99
debug: exec

exec: 
	@for f in $(SOURCES:.c=) ;  \
  	  do \
		$(CC) $(CFLAGS) -o $$f $$f.c $(LIBS) ;\
	done

tests: exec
	@for f in $(SOURCES:.c=) ;  \
		do \
		  	[ $$f != "matrix_producer" ] &&  ./$$f ; \
	done
	
#%.o: %.c
#	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean mrproper

clean:
	@for f in $(SOURCES:.c=) ;  \
		do \
		  rm ./$$f ; \
	done

mrproper:
	@rm $(EXEC)

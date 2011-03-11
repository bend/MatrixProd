#CFLAGS+=-W -Wall -Lpthread -Lgmp -Werror -ansi -pedantic 
CFLAGS=-W -Wall -Lpthread -lgmp
EXEC=matrix
SOURCES=$(wildcard *.c)
LIBS=$(filter-out ../main.c, $(wildcard ../*.c))
#echo $(filter-out ../main.c, $(LIBS)) ;
OBJECTS=$(SOURCES:.c=.o)

all: tests
debug: CFLAGS+= -DDEBUG -g
debug: $(EXEC)

exec: 
	for f in $(SOURCES:.c=) ;  \
  	  do \
		$(CC) $(CFLAGS) -o $$f $$f.c $(LIBS) ;\
	  done

tests: exec
	@for f in $(SOURCES:.c=) ;  \
		do \
		  ./$$f ; \
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

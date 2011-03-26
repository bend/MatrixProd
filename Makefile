CFLAGS+=-W -Wall -Lpthread -Lgmp -Werror -std=c99 -pedantic -g
#CFLAGS+=-W -Wall -Lpthread -Lgmp  -ansi -pedantic 
LDFLAGS+=-lpthread -lgmp
EXEC=matrix_prod
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

all: $(EXEC)
debug: CFLAGS+= -W -Wall -Lpthread -Lgmp -Werror -std=c99 -pedantic -DDEBUG -g
debug: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean mrproper

clean:
	@rm $(OBJECTS)

mrproper:
	@rm $(EXEC)

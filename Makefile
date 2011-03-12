#CFLAGS+=-W -Wall -Lpthread -Lgmp -Werror -ansi -pedantic 
CFLAGS+=-W -Wall -Lpthread -Lgmp  -ansi -pedantic 
LDFLAGS+=-Lpthread -lgmp
#CFLAGS+=-Wall
EXEC=matrix
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

all: $(EXEC)
debug: CFLAGS+= -DDEBUG -g
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

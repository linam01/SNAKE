TARGET = snake

DEPENDS = snk.c config.h  type.h fonction.h 
OBJECTS = snk.o fonction.o


##########################################################"                                         
CC=gcc

CFLAGS = -g -O2 -Wall `pkg-config --cflags MLV`
LDLIBS = `pkg-config --libs MLV`

all: $(TARGET) clean

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJECTS)
	gcc -o $@ $^ $(LDLIBS)

.PHONY: clean

clean:
	-rm -rf $(OBJECTS) 



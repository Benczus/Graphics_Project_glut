CC = gcc

# Debug
CFLAGS = -Iinclude -I../src -g -O2 -Wall
LDFLAGS = -lGL -lGLU -lglut -lSOIL -lm

SOURCES = \
	camera.c \
    draw.c \
    model.c \
AABB.c\
    main.c

OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = grafika

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS)

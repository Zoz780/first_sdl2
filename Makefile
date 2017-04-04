CC = g++

CFLAGS = -I/usr/include/GL -g -O2 -std=c++11 -Wall
LDFLAGS = -lSDL2 -lGLEW -lGL -lGLU -lSOIL

SOURCES = Camera.cpp  Main.cpp  MainGame.cpp  ModelDrawer.cpp  ModelLoader.cpp  Sprite.cpp

OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = first_sdl2

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS)

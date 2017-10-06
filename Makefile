CC = g++

CFLAGS = -I/usr/include/GL -g -O2 -std=c++11 -Wall
LDFLAGS = -lSDL2 -lGLEW -lGL -lGLU -lSOIL -lSDL_mixer

SOURCES = Camera.cpp  Main.cpp  MainGame.cpp ModelLoader.cpp Map.cpp Position.cpp Utils.cpp Platform.cpp VboDrawer.cpp MainMenu.cpp Action.cpp DrawHeightMapVBO.cpp HeightMap.cpp Vec3.cpp Sound.cpp Materials.cpp Texture.cpp BulletCalcs3D.cpp Entity.cpp Player.cpp IngameElements2D.cpp

OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = first_sdl2

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS)

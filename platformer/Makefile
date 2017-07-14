OS := $(shell uname)

$(info $(OS))

G_FLAGZ=-std=c++11 -Wall -g

ifeq ($(OS), Darwin)
    FLAGZ=$(G_FLAGZ) -lninage -framework OpenGL -framework GLUT -lSDL2_image -lSDL2_ttf -lSDL2
else
    FLAGZ=$(G_FLAGZ) -std=c++11 -lninage -lGL -lglut -lSDL2_image -lSDL2_ttf -lGLU -lSDL2
endif

OFILES=\
       main.o\
       MainScene.o\
       Block.o\
       Player.o\
       Fireball.o


output: $(OFILES)
	g++ $(OFILES) $(FLAGZ) -o app.out

main.o: src/main.cpp
	g++ $(G_FLAGZ) -c src/main.cpp

MainScene.o: src/MainScene.cpp src/MainScene.h
	g++ $(G_FLAGZ) -c src/MainScene.cpp

Block.o: src/Block.cpp src/Block.h
	g++ $(G_FLAGZ) -c src/Block.cpp

Player.o: src/Player.cpp src/Player.h
	g++ $(G_FLAGZ) -c src/Player.cpp

Fireball.o: src/Fireball.cpp src/Fireball.h
	g++ $(G_FLAGZ) -c src/Fireball.cpp

clean:
	-rm *.out
	-rm *.o

OS := $(shell uname)

$(info $(OS))

G_FLAGZ=-std=c++11 -Wall -g

ifeq ($(OS), Darwin)
    FLAGZ=$(G_FLAGZ) -lninage -framework OpenGL -framework GLUT -lresourcemanager -lSDL2_image -lSDL2_ttf -lSDL2
else
    FLAGZ=$(G_FLAGZ) -std=c++11 -lninage -lresourcemanager -lGL -lglut -lSDL2_image -lSDL2_ttf -lGLU -g -lSDL2
endif

OFILES=\
       main.o\
       MainScene.o\
       Ground.o


output: $(OFILES)
	g++ $(OFILES) $(FLAGZ) -o app.out

main.o: src/main.cpp
	g++ $(G_FLAGZ) -c src/main.cpp

MainScene.o: src/MainScene.cpp src/MainScene.h
	g++ $(G_FLAGZ) -c src/MainScene.cpp

Ground.o: src/Ground.cpp src/Ground.h
	g++ $(G_FLAGZ) -c src/Ground.cpp

clean:
	-rm *.out
	-rm *.o

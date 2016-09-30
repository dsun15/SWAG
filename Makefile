OBJS = main.cpp Movable.o AutoMovable.o GameScreen.o MenuScreen.o TitleScreen.o Screen.o
CC = g++

CCFLAGS = -std=c++11 -Wall -Wextra -Wpedantic

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm 

OBJ_NAME = main

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(CCFLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

Movable.o: Movable.cpp
	$(CC) -c Movable.cpp $(CCFLAGS) #$(LINKER_FLAGS)
AutoMovable.o: AutoMovable.cpp
	$(CC) -c AutoMovable.cpp $(CCFLAGS) #$(LINKER_FLAGS)
Screen.o: Screen.cpp
	$(CC) -c Screen.cpp $(CCFLAGS) #$(LINKER_FLAGS)
GameScreen.o: GameScreen.cpp
	$(CC) -c GameScreen.cpp $(CCFLAGS) #$(LINKER_FLAGS)
MenuScreen.o: MenuScreen.cpp
	$(CC) -c MenuScreen.cpp $(CCFLAGS) #$(LINKER_FLAGS)
TitleScreen.o: TitleScreen.cpp
	$(CC) -c TitleScreen.cpp $(CCFLAGS) #$(LINKER_FLAGS)

clean : 
	rm main *.o *~

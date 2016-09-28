OBJS = main.cpp Movable.cpp AutoMovable.cpp Screen.cpp GameScreen.cpp
CC = g++

COMPILER_FLAGS = -std=c++11 -Wall -Wextra -Wpedantic

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm 

OBJ_NAME = main

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean : 
	rm main

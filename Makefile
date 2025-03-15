OBJS = $(wildcard *.cpp)

CC = g++

COMPILER_FLAGS = -Wall -Werror -std=c++17 `sdl2-config --cflags --libs` -lSDL2_image

LINKER_FLAGS = -lSDL2

OBJ_NAME = main 

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm -rf $(OBJ_NAME)
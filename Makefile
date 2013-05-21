CXX=clang++
CC=clang++
CXXFLAGS:=$(shell sdl-config --cflags)
LDLIBS:=-lstdc++ -lncurses -lboost_system -lboost_filesystem $(shell sdl-config --libs) -lSDL_ttf
ENGINE=$(patsubst %.cpp,%.o,$(wildcard Engine/*.cpp))
LEVEL=$(patsubst %.cpp,%.o,$(wildcard Level/*.cpp))
LOGIC=$(patsubst %.cpp,%.o,$(wildcard Logic/*.cpp))
SCREEN=$(patsubst %.cpp,%.o,$(wildcard Screens/*.cpp))
.PHONY: clean
sokoban: sokoban.o \
		 ${ENGINE} \
		 ${LEVEL} \
		 ${LOGIC} \
		 ${SCREEN}
sokoban.o: Logic/SokobanLogic.h \
	       Logic/GameLogic.h \
		   Engine/CursesEngine.h
%.o: %.cpp %.h
clean:
	rm *.o
	rm */*.o
	rm sokoban

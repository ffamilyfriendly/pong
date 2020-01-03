flags= \
	-lGL \
	-lglut

all:
	g++ engine.cpp elements.cpp ${flags} -o game
GLUTFLAGS = -Wall -lglut -lGLU -lGL
FLAGS = -Wall

default: all

all: main.o janela.o retangulo.o circulo.o tinyxml2.o funcoes_opengl.o
	g++ -o trabalhocg janela.o retangulo.o circulo.o tinyxml2.o main.o funcoes_opengl.o $(GLUTFLAGS)

tinyxml2.o: tinyxml2.cpp tinyxml2.h
	g++ $(FLAGS) -c tinyxml2.cpp

janela.o: janela.cpp janela.h tinyxml2.h
	g++ $(FLAGS) -c janela.cpp

circulo.o: circulo.cpp circulo.h tinyxml2.h
	g++ -c circulo.cpp $(GLUTFLAGS)

retangulo.o: retangulo.cpp retangulo.h tinyxml2.h
	g++ -c retangulo.cpp $(GLUTFLAGS)

main.o: main.cpp janela.h funcoes_opengl.h circulo.h retangulo.h
	g++ -c main.cpp $(GLUTFLAGS)

funcoes_opengl.o: funcoes_opengl.h funcoes_opengl.cpp circulo.h retangulo.h
	g++ -c funcoes_opengl.cpp $(GLUTFLAGS)

clean:
	rm *.o trabalhocg

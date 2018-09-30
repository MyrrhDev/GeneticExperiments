OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Wno-uninitialized  -Wno-sign-compare -std=c++0x

program.exe: program.o Cromosomas.o Individuo.o Familias.o Especie.o 
	g++ -o program.exe program.o Cromosomas.o Individuo.o Familias.o Especie.o

Cromosomas.o:  Cromosomas.cc Cromosomas.hh 
	g++ -c Cromosomas.cc $(OPCIONS)
Individuo.o:  Individuo.cc Individuo.hh 
	g++ -c Individuo.cc $(OPCIONS)
Familias.o:  Familias.cc Familias.hh
	g++ -c Familias.cc $(OPCIONS)
Especie.o:  Especie.cc Especie.hh 
	g++ -c Especie.cc $(OPCIONS)
program.o:  program.cc
	g++ -c program.cc $(OPCIONS)

clean:
	rm *.o
	rm *.exe

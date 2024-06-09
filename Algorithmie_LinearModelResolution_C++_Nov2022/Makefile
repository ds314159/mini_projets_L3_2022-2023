Matrix.o : Matrix.cpp Matrix.h
	g++ -c -O Matrix.cpp
	
LinearSystem.o : LinearSystem.cpp LinearSystem.h
	g++ -c -O LinearSystem.cpp
	
main.o : main.cpp Matrix.h LinearSystem.h
	g++ -c -O main.cpp
	
main : Matrix.o LinearSystem.o main.o
	g++ -O -o main Matrix.o LinearSystem.o main.o

main : main.o BasicSIR.o VitalDynamicsSIR.o SIRV.o SEIR.o
	g++ -I Eigen -O -o main main.o BasicSIR.o VitalDynamicsSIR.o SIRV.o SEIR.o

main.o : main.cpp BasicSIR.h VitalDynamicsSIR.h SIRV.h SEIR.h
	g++ -I Eigen -c -O main.cpp

SIRV.o : SIRV.cpp SIRV.h BasicSIR.h
	g++ -I Eigen -c -O SIRV.cpp

SEIR.o : SEIR.cpp SEIR.h BasicSIR.h
	g++ -I Eigen -c -O SEIR.cpp

VitalDynamicsSIR.o : VitalDynamicsSIR.cpp VitalDynamicsSIR.h BasicSIR.h
	g++ -I Eigen -c -O VitalDynamicsSIR.cpp

BasicSIR.o : BasicSIR.cpp BasicSIR.h
	g++ -I Eigen -c -O BasicSIR.cpp
	


	



	

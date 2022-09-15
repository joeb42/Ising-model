CPP := g++-11

CFLAGS := -fopenmp -std=c++17 

GSL_COMP := -I/usr/local/include 

GSL_LINK := -L/usr/local/lib -lgsl -lgslcblas

COMPILE_COMMAND := $(CPP) $(CFLAGS) 

# physics: Lattice.o physics.o
# 	$(COMPILE_COMMAND) $(GSL_LINK) physics.o Lattice.o -o physics.app

# physics.o: physics.cpp
# 	$(COMPILE_COMMAND) $(GSL_COMP) -c physics.cpp -o physics.o 

# Lattice.o: Lattice.cpp 
# 	$(COMPILE_COMMAND) $(GSL_COMP) -c Lattice.cpp -o Lattice.o 

# all: physics

main: main.o Lattice2D.o LatticeBase.o
	$(COMPILE_COMMAND) $(GSL_LINK) main.o Lattice2D.o LatticeBase.o -o main.app

main.o: main.cpp
	$(COMPILE_COMMAND) $(GSL_COMP) -c main.cpp -o main.o

Lattice2D.o: Lattice2D.cpp
	$(COMPILE_COMMAND) $(GSL_COMP) -c Lattice2D.cpp -o Lattice2D.o

LatticeBase.o: LatticeBase.cpp
	$(COMPILE_COMMAND) $(GSL_COMP) -c LatticeBase.cpp -o LatticeBase.o
	
test: test.o
	$(COMPILE_COMMAND) $(GSL_LINK) test.o -o test.app

test.o: test.cpp 
	$(COMPILE_COMMAND) $(GSL_COMP) -c test.cpp -o test.o

clean:
	rm -f *.o *.app

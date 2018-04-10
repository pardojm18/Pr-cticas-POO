                        #Makefile 2.0
DTA = ../Tests-auto
CXX = clang++-3.9
CPPFLAGS = -I$(DTA) -I. -DP0
CXXFLAGS = -g -Wall -std=c++11 -pedantic -O
VPATH = $(DTA):.
BASURA = test-auto *.o *~

all: test-P0-auto test-P0-consola

test-P0-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o fecha.o cadena.o
	$(CXX) $(CXXFLAGS) -o $@ $^
test-P0-consola: test-P0-consola.o fecha.o cadena.o
	$(CXX) $(CXXFLAGS) -o $@ $^
test-P0-consola.o: test-P0-consola.cpp
checks: ; ${MAKE} -f Make_check.mk $@
test-caso0-fecha-auto.o: test-auto.hpp fct.h
test-caso0-cadena-auto.o: test-auto.hpp fct.h
fecha.o: fecha.hpp
cadena.o: cadena.hpp
clean:
	$(RM) $(BASURA)

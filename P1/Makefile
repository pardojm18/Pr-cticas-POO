DTA = ../Tests-auto
CXX = clang++
CPPFLAGS = -I$(DTA) -I. -DP1
CXXFLAGS = -g -Wall -std=c++11 -pedantic -O
VPATH = $(DTA):.

all: test-P1-auto test-P1-consola

test-P1-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o fecha.o cadena.o
	$(CXX) $(CXXFLAGS) -o $@ $^
test-P1-consola: test-P1-consola.o fecha.o cadena.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test-P1-consola.o: test-P1-consola.cpp
checks: ; ${MAKE} -f Make_check.mk $@
test-caso0-fecha-auto.o: test-auto.hpp fct.h
test-caso0-cadena-auto.o: test-auto.hpp fct.h
fecha.o: fecha.hpp
cadena.o: cadena.hpp

clean:
	$(RM) test-auto *.o *~

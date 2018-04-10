#include <iostream>
#include <stdio.h>
#include "cadena.hpp"
#include "cadena.cpp"
using namespace std;

int main(int argc, char const *argv[])
{
	Cadena a("Hola");
	cout << a << endl;
	Cadena c = a + " y adios";
	cout << c << endl;

	return 0;
}
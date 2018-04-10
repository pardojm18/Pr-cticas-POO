#include <iostream>
#include <stdio.h>
#include "cadena.hpp"
#include "cadena.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
	Cadena a ("hola");
	cout << a << endl;;
	cin >> a;
	cout << a << endl;
	return 0;
}
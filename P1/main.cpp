#include <iostream>
#include <stdio.h>
#include "fecha.hpp"
#include "fecha.cpp"
using namespace std;

int main(int argc, char const *argv[])
{
	const Fecha a ("23/09/2015");

	cout << a << endl;

	return 0;
}
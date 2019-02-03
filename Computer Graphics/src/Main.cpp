#include <iostream>

#include "complex.h"

int main(int argc, char* argv[])
{
	//Utilizando el constructor por default
	cgmath::complex c1;

	//Utilizando el constructor que recibe 2 floats
	cgmath::complex c2(1.0f, -2.0f);

	std::cout << c1 << std::endl;
	std::cout << c2 << std::endl;

	c1.add(c2);
	std::cout << c1 << std::endl;

	c1 += c2;
	std::cout << c1 << std::endl;

	cgmath::complex c3 = cgmath::complex::add(c1, c2);
	std::cout << c3 << std::endl;

	std::cout << c1+c2+c3 << std::endl;

	std::cout << "Press [ENTER] to continue" << std::endl;
	std::cin.get();

	return 0;
}
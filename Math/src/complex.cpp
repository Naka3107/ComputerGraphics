#include "complex.h"

cgmath::complex::complex() : real(0.0f), imag(0.0f) {

}

cgmath::complex::complex(float real, float imag) :real(real), imag(imag) {
	
}

void cgmath::complex::print() const {
	std::cout << real << " + " << imag << "i";
}

void cgmath::complex::add(const complex& other) {
	real += other.real;
	imag += other.imag;
}

cgmath::complex& cgmath::complex::operator+=(const complex & other)
{
	real += other.real;
	imag += other.imag;

	return *this;
}

cgmath::complex cgmath::complex::add(const complex& a, const complex& b)
{
	return cgmath::complex(a.real + b.real, a.imag + b.imag);
}

#pragma once

#include <iostream>

namespace cgmath {
	class complex {
	public:
		//Estas dos variables se almacenan en memoria de manera contigüa.
		//Sólo las variables se almacenan, los métodos no.
		float real;
		float imag;

		complex();
		complex(float real, float imag);

		//Manera tradicional de imprimir una representación de esta clase.
		//Muy común en otros lenguajes.
		void print() const;
		
		friend inline std::ostream& operator<< (std::ostream& os, const complex& c)	{
			os << c.real << " + " << c.imag << "i" << std::endl;
			return os;
		}

		void add(const complex& other);
		complex& operator+=(const complex& other);

		static complex add(const complex& a, const complex& b);
	};
	inline complex operator+(const complex& a, const complex& b) {
		return complex(a.real + b.real, a.imag + b.imag);
	}
}
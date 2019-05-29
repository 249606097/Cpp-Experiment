#ifndef CIR
#define CIR

#include "Shape.h"

class Circle: public Shape
{
	public:
		Circle(double radius);
		double getCircumference();
		void print_self();

	private:
		double radius;
};


#endif
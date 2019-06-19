#ifndef REC
#define REC

#include "Shape.h"

class Rectangle: public Shape
{
	public:
		Rectangle(double length, double width);
		double getCircumference();
		void print_self();

		double get_length();

	private:
		double length;
		double width;
};


#endif
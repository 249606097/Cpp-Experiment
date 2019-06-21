#ifndef RIG
#define RIG

#include "Shape.h"

class RightTriangle : public Shape
{
	public:
		RightTriangle(double catheti_1, double catheti_2);
		double getCircumference();
		void print_self();

	private:
		double catheti_1; // ֱ�Ǳ� 
		double catheti_2;
};

#endif
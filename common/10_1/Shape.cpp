#include "Shape.h"

#include <iostream>
#include <iomanip>

using namespace std;

Shape::Shape()
{
	;
}

double Shape::getCircumference()
{
	return this->Circumference;
}

void Shape::printCircumference()
{
	cout << "ÖÜ³¤" << this->Circumference << setprecision(2) << endl;
}

bool Shape::operator>(Shape &one)
{
	if (this->Circumference > one.Circumference)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Shape::print_self()
{

}
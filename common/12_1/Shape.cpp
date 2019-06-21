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

void Shape::set_price(double price)
{
	this->price = price * this->Circumference;
}

double Shape::get_price()
{
	return this->price;
} 

int Shape::get_classId()
{
	return this->classId;
}
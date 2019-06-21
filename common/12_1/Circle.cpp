#include "Circle.h"

#include <iostream>
#include <iomanip>

using namespace std;

Circle::Circle(double radius)
{
	this->classId = 1;

	this->radius = radius; 
	
	this->Circumference = getCircumference();
}

double Circle::getCircumference()
{
	return this->radius * 2 * 3.14;
}

void Circle::print_self()
{
	//cout << "Ô²£¬" << "°ë¾¶" << this->radius << "£¬";
	//this->printCircumference();
	cout << setw(8) << "Ô²£º" << this->get_classId() << ' ' << "Circle" << ' ' << "radius:" << this->radius;
	cout << ' ' << "price:" << this->get_price() << endl;
}
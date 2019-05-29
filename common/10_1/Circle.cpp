#include "Circle.h"

#include <iostream>

using namespace std;

Circle::Circle(double radius)
{
	this->radius = radius;
	
	this->Circumference = getCircumference();
}

double Circle::getCircumference()
{
	return this->radius * 2 * 3.14;
}

void Circle::print_self()
{
	cout << "Ô²£¬" << "°ë¾¶" << this->radius << "£¬";
	this->printCircumference();
}
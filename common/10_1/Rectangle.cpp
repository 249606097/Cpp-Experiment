#include "Rectangle.h"

#include <iostream>

using namespace std;

Rectangle::Rectangle(double length, double width)
{
	this->length = length;
	this->width = width;

	this->Circumference = this->getCircumference();
}

double Rectangle::getCircumference()
{
	return this->length * 2 + this->width * 2;
}

void Rectangle::print_self()
{
	cout << "长方形，" << "长" << this->length << "，" << "宽" << this->width << "，";
	this->printCircumference();
}
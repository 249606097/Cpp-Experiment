#include "Rectangle.h"

#include <iostream>
#include <iomanip>

using namespace std;

Rectangle::Rectangle(double length, double width)
{
	this->classId = 2;

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
	//cout << "�����Σ�" << "��" << this->length << "��" << "��" << this->width << "��";
	//this->printCircumference(); 
	cout << setw(8) << "�����Σ�" << this->get_classId() << ' ' << "Rectangle" << ' ' << "width:" << this->width << ' ' << "height:" << this->length;
	cout << ' ' << "price:" << this->get_price() << endl;
}

double Rectangle::get_length()
{
	return this->length;
}
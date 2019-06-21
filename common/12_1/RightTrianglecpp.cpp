#include "RightTriangle.h"

#include <iostream>
#include <iomanip>

using namespace std;

RightTriangle::RightTriangle(double catheti_1, double catheti_2)
{
	this->classId = 3;
	
	this->catheti_1 = catheti_1;
	this->catheti_2 = catheti_2;

	this->Circumference = this->getCircumference();
}

double RightTriangle::getCircumference()
{
	return this->catheti_1 + this->catheti_2 + sqrt(this->catheti_1*this->catheti_1 + this->catheti_2*this->catheti_2);
}

void RightTriangle::print_self()
{
	//cout << "三角形，" << "直角边" << this->catheti_1 << "，" << "直角边" << this->catheti_2 << "，";
	//this->printCircumference(); 
	cout << setw(8) << "三角形：" << this->get_classId() << ' ' << "RightTriangle" << ' ' << "catheti:" << this->catheti_1 << ' ' << this->catheti_2;
	cout << ' ' << "price:" << this->get_price() << endl;
}
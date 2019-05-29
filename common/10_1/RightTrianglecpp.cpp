#include "RightTriangle.h"

#include <iostream>

using namespace std;

RightTriangle::RightTriangle(double catheti_1, double catheti_2)
{
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
	cout << "�����Σ�" << "ֱ�Ǳ�" << this->catheti_1 << "��" << "ֱ�Ǳ�" << this->catheti_2 << "��";
	this->printCircumference();
}
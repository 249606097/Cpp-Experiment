#include "Square.h"
#include <iostream>
#include <iomanip>

using namespace std;

Square::Square(double length) : Rectangle(length, length)
{
	this->classId = 4;
}

void Square::print_self()
{
	//cout << "�����Σ�" << "�߳�" << this->get_length() << "��";
	//this->printCircumference(); 
	cout << setw(8) << "�����Σ�" << this->get_classId() << ' ' << "Square" << ' ' << "length:" << this->get_length();
	cout << ' ' << "price:" << this->get_price() << endl;
}
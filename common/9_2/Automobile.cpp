#include "Automobile.h"

#include <iostream>

using namespace std;

Automobile::Automobile(string number)
{
	this->number = number;
}

void Automobile::enter(Park *park)
{
	park->park(this);
}

void Automobile::leave(Park *park)
{
	cout << this->number << "�뿪ͣ������";
	park->reclaimSpace(this);
	pay(*park);
}

string Automobile::get_number()
{
	return this->number;
}

Car::Car(string number, string brand): Automobile(number)
{
	this->brand = brand;
}

void Car::pay(Park &park)
{
	cout << "����ͣ����1Ԫ" << endl;
	park.get_money(1);
}

Truck::Truck(string number, double weight) : Automobile(number)
{
	this->weight = weight;
}

void Truck::pay(Park &park)
{
	cout << "����ͣ����3Ԫ" << endl;
	park.get_money(3);
}

Bus::Bus(string number, int carrier) : Automobile(number)
{
	this->carrier = carrier;
}

void Bus::pay(Park &park)
{
	cout << "����ͣ����2Ԫ" << endl;
	park.get_money(2);
}
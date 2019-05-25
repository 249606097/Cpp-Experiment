#ifndef AUTOMOBILE_H
#define AUTOMOBILE_H

#include <string>

using namespace std;

#include "Park.h"

class Park;

class Automobile
{
	public:
		Automobile(string number);
		void enter(Park *park);
		void leave(Park *park);
		string get_number();
	protected:
		virtual void pay(Park &park) = 0;  // 向停车场支付停车费，由派生类实现
		string number;
};

class Car : public Automobile 
{
	public:
		Car(string number, string brand);
		void pay(Park &park);
	private:
		string brand;
};

class Truck : public Automobile
{
	public:
		Truck(string number, double weight);
		void pay(Park &park);
	private:
		double weight;
};

class Bus : public Automobile
{
	public:
		Bus(string number, int carrier);
		void pay(Park &park);
	private:
		int carrier;
};

#endif
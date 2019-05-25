#ifndef PARK_H
#define PARK_H

class Automobile;

#include "Automobile.h"

class Park
{
	public:
		Park(int total);
		~Park();

		void showInfo();
		void park(Automobile* one);
		void reclaimSpace(Automobile *one);

		void get_money(int money);

	private:
		int total;
		int number = 0;
		Automobile **spaces;
		double money = 0;

		bool can_park();
};

#endif
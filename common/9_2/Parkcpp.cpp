#include "Park.h"

#include <iostream>

using namespace std;

Park::Park(int total)
{
	this->total = total;

	this->spaces = new Automobile *[this->total];

	for (int i = 0; i < this->total; i++)
	{
		this->spaces[i] = NULL;
	}
}

Park::~Park()
{
	//delete [] this;
}

void Park::showInfo()
{
	cout << "ͣ����Ŀǰͣ����" << this->number << "��������";
	for (int i = 0; i < this->total; i++)
	{
		if (this->spaces[i] != NULL)
		{
			cout << this->spaces[i]->get_number() << "��";
		}
	}
	cout << "������" << this->money << "Ԫͣ����" << endl;
}

bool Park::can_park()
{
	if (this->number < this->total)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Park::park(Automobile* one)
{
	if (this->can_park())
	{
		for (int i = 0; i < this->total; i++)
		{
			if (this->spaces[i] == NULL)
			{
				cout << one->get_number() << "����ͣ����������ͣ��λ" << endl;
				this->spaces[i] = one;
				this->number++;
				break;
			}
		}
	}
	else
	{
		cout << "�޷�Ϊ" << one->get_number() << "����ͣ��λ" << endl;
	}
}

void Park::reclaimSpace(Automobile *one)
{
	for (int i = 0; i < this->total; i++)
	{
		if (this->spaces[i] == one)
		{
			this->spaces[i] = NULL;
			this->number--;
		}
	}
}

void Park::get_money(int money)
{
	this->money += money;
}
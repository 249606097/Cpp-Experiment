#include <iostream>
#include <cstdlib>

#include "Circle.h"
#include "Rectangle.h"
#include "RightTriangle.h"

using namespace std;

int main()
{
	Shape** arr;
	arr = new Shape *[2];

	int total = 0;
	int n = 0;

	while (n != -1)
	{
		cout << "1. 圆" << endl;
		cout << "2. 长方形" << endl;
		cout << "3. 三角形" << endl;
		cout << "-1. 退出" << endl;
		cin >> n;

		double a;
		double b;
		
		switch (n)
		{
		case 1:
			cout << "输入半径：";
			cin >> a;
			arr[total] = new Circle(a);
			break;
		
		case 2:
			cout << "输入长、宽：";
			cin >> a;
			cin >> b;
			arr[total] = new Rectangle(a, b);
			break;
		
		case 3:
			cout << "输入两直角边：";
			cin >> a; 
			cin >> b;
			arr[total] = new RightTriangle(a, b);
			break;
		
		default:
			break;
		}

		if (n == -1)
		{
			break;
		}

		total++;
	}

	int max;
	for (int i = 0; i < total; i++)
	{
		max = i;
		for (int j = max + 1; j < total; j++)
		{
			if (*arr[j] > *arr[max])
			{
				max = j;
			}
		}
		
		if (max != i)
		{
			Shape* temp;
			temp = arr[max];
			arr[max] = arr[i];
			arr[i] = temp;
		}
	}


	for (int i = 0; i < total; i++)
	{
		arr[i]->print_self();
	}
	
	system("PAUSE");
	return 0;
}
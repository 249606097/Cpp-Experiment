#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

#include "Circle.h"
#include "Rectangle.h"
#include "RightTriangle.h"
#include "Square.h"

#include "FileNotFoundException.h"

using namespace std;

int main()
{
	Shape* arr[4];
	string s;

	fstream fp;

	// 读标准文件
	int total = 0;
	try
	{ 
		fp.open("D:\\Study\\workstation\\vs2015_files\\Project5\\Debug\\Shapes.txt");

		if (!fp)
		{
			throw(FileNotFoundException("not found"));
			return 1;
		}

		while (!fp.eof())
		{
			fp >> s;
			//cout << stof(s.substr(0, s.length() - 1)) << endl;
			cout << s;

			switch ((int)stof(s.substr(0, s.length() - 1)))
			{
			case 1:
				arr[total] = new Circle(3);
				break;

			case 2:
				arr[total] = new Rectangle(3, 3);
				break;

			case 3:
				arr[total] = new RightTriangle(3, 3);
				break;

			case 4:
				arr[total] = new Square(3);
				break;

			default:
				break;
			}

			fp >> s;
			//cout << s.substr(0, s.length() - 1) << endl;
			cout << s;

			fp >> s;
			cout << stof(s) << endl; // stof() 将字符串数字 转化成 float 
			arr[total]->set_price(stof(s));

			total++;
			//throw(FileNotFoundException("file error"));
		}
	}
	catch (FileNotFoundException& e)
	{
		cout << e.getMessage() << endl;
	}
	
	cout << endl;

	fp.close();

	// 排序
	int max;
	for (int m = 0; m < total; m++)
	{
		max = m;
		for (int n = max + 1; n < total; n++)
		{
			if (*arr[n] > *arr[max])
			{
				max = n;
			}
		}

		if (max != m)
		{
			Shape* temp;
			temp = arr[max];
			arr[max] = arr[m];
			arr[m] = temp;
		}
	}

	for (int i = 0; i < total; i++)
	{
		arr[i]->print_self();
	}
	cout << endl;

	// 将类写入文件
	for (int i = 0; i < 4; i++)
	{
		switch (arr[i]->get_classId())
		{
		case 1:
			fp.open("D:\\Study\\workstation\\vs2015_files\\Project5\\Debug\\Circle.dat", ios::out | ios::binary);
			fp.write((char*)arr[i], sizeof(Circle));
			fp.close();

			break;

		case 2:
			fp.open("D:\\Study\\workstation\\vs2015_files\\Project5\\Debug\\Rectangle.dat", ios::out | ios::binary);
			fp.write((char*)arr[i], sizeof(Rectangle));
			fp.close();

			break;

		case 3:
			fp.open("D:\\Study\\workstation\\vs2015_files\\Project5\\Debug\\Rightrangle.dat", ios::out | ios::binary);
			fp.write((char*)arr[i], sizeof(RightTriangle));
			fp.close();

			break;

		case 4:
			fp.open("D:\\Study\\workstation\\vs2015_files\\Project5\\Debug\\Square.dat", ios::out | ios::binary);
			fp.write((char*)arr[i], sizeof(Square));
			fp.close();

			break;
		}
	}

	// 从文件读出数据 
	Circle temp_circle = Circle(0);
	fp.open("D:\\Study\\workstation\\vs2015_files\\Project5\\Debug\\Circle.dat", ios::in | ios::binary);
	fp.read((char*)&temp_circle, sizeof(Circle));
	temp_circle.print_self();
	fp.close();

	Rectangle temp_rectangle = Rectangle(0, 0);
	fp.open("D:\\Study\\workstation\\vs2015_files\\Project5\\Debug\\Rectangle.dat", ios::in | ios::binary);
	fp.read((char*)&temp_rectangle, sizeof(Rectangle));
	temp_rectangle.print_self();
	fp.close();

	RightTriangle temp_rightTriangle = RightTriangle(0, 0);
	fp.open("D:\\Study\\workstation\\vs2015_files\\Project5\\Debug\\Rightrangle.dat", ios::in | ios::binary);
	fp.read((char*)&temp_rightTriangle, sizeof(RightTriangle));
	temp_rightTriangle.print_self();
	fp.close();

	Square temp_square = Square(0);
	fp.open("D:\\Study\\workstation\\vs2015_files\\Project5\\Debug\\Square.dat", ios::in | ios::binary);
	fp.read((char*)&temp_square, sizeof(Square));
	temp_square.print_self();
	fp.close();

	system("PAUSE");
	return 0;

}
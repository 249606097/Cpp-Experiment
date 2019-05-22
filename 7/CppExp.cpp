#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "highgui.h"
#include "Image.h"

Matrix Matrix::operator*(const Image &img)  //两幅尺寸相同的图像，对应像素点的数值相乘；
{
	if (this->height != img.height || this->width != img.width)
	{
		Matrix m;
		cout << "error" << endl;
		return m;
	}

	Matrix m(this->height, this->width);

	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
		{
			m.data[i][j] = this->data[i][j] * img.data[i][j];
			if (m.data[i][j] > 255)
			{
				m.data[i][j] = 255;
			}
		}

	return m;
}

Matrix Matrix::operator/(const Image &img)  //两幅尺寸相同的图像，对应像素点的数值相除；
{
	if (this->height != img.height || this->width != img.width)
	{
		Matrix m;
		cout << "error" << endl;
		return m;
	}

	Matrix m(this->height, this->width);

	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
		{
			m.data[i][j] = this->data[i][j] / img.data[i][j];
			if (m.data[i][j] > 255)
			{
				m.data[i][j] = 255;
			}
		}

	return m;
}

int main(int argc, char* argv[])
{
	Image img1("scene2_fg.jpg");
	Image img2("scene2_bg.jpg");

	img1.Show("img1");
	img2.Show("img2");

	img1.Read("scene1_fg.jpg");
	img2.Read("scene1_bg.jpg");
	
	img2.Resize(img1.Height(), img1.Width());
	img1.Show("img1");
	img2.Show("img2");
	
	Image sub(Sub(img1, img2));
	sub.Show("sub");

	Image sum(Add(img1, img2));
	sum.Show("sum");

	Image product(sum*2);
	(-product).Show("product");

	Image bw;
	bw = sub.gray2bw(0.9);
	bw.Show("bw");

	int n;
	while (1)
	{
		int num;
		cout << "对img1进行操作，输入选择" << endl;
		cout << "	1. + " << endl;
		cout << "	2. - " << endl;
		cout << "	3. ++" << endl;
		cout << "	4. --" << endl;
		cout << "	0. exit" << endl;
		cin >> n;

		switch (n)
		{
		case 1:
			cout << "type a number ";
			cin >> num;

			((Image)(img1 + num)).Show("img1");
			break;
		case 2:
			cout << "type a number ";
			cin >> num;

			((Image)(img1 - num)).Show("img1");
			break;
		case 3:
			img1++;
			img1.Show("img1");
			break;
		case 4:
			img1--;
			img1.Show("img1");
			break;
		case 0:
			cout << "Bye" << endl;
			break;
		default:
			cout << "Error, Type again" << endl;
			break;
		}

		if (n == 0)
			break;
	}
	return 0;
}

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "highgui.h"
#include "Image.h"

int main(int argc, char* argv[])
{
	Matrix m(160000, 1);
	for (int i = 0; i < 160000; i++)
	{
		m.At(i, 0) = i%256;
		//  m.Set(i,0,i%256);
	}
	m.Reshape(400, 400);
	Image img(m);
	img.Show("Matrix");

	Matrix d = m.MajorDiagonal();
	Image *p = new Image(d);
	p->Show("pImage");
	p->Reshape(20,20);
	p->Show("pImageReshaped");

	delete p;
	p = NULL;



	/*
	Image im("Fruits.jpg");
	//im.Resize(200, 200);
	im.Show("Resized Image");
	im.Rotate(40);
	im.Show("Rotated Image");
	*/

	Image img1("Fruits.jpg"); 
	img1.Show("Image2");
	Image img2("Word.jpg"); 
	img2.Show("Image1");
	//��ͼƬ���
	Image img_add(Add(img1, img2)) ;
	img_add.Show("Add");

	//��ͼƬ���
	Image img_sub(Sub(img1, img2));
	img_sub.Show("Sub");


	//ͼƬ��ת��
	Image img3("lena.jpg");
	img3.Transpose();
	img3.Show("Transpose");

	//���ұ�ƴ��ͼƬ��
	Image img4("Airplane.jpg"); 
	Image img5("Baboon.jpg");
	img4.Cat(img5,1);
	img4.Show("CATRight");
	//������ƴ��ͼƬ
	Image img6("Airplane.jpg"); 
	Image img7("Baboon.jpg");
	img6.Cat(img7,2);
	img6.Show("CATDown");
	return 0;
}

#include "Image.cpp"
#include <iostream>

using namespace std;

int main()
{
	Image img;
	img.Read("Fruits.jpg");

	img.Write("FruitsCopy.jpg");
		
	cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
	img.Show("Image");

	//���·�ת img.Flip(true)
	img.Flip(true);
	img.Show("Image");

	// ���ҷ�ת img.Filp(false)
	img.Flip(false);
	img.Show("Image");

	// ͼ��Ŵ� img.Resize(true)
	img.Resize(true);
	img.Show("Image");

	//ͼ����С img.Resize(false)
	img.Resize(false);
	img.Show("Image");

	//��ȡͼ���ĳ�������ֵ,���޸�
	cout << int(img.At(100, 100));
	img.Set(0, 100, 100);

    //ʹ�ÿ������캯�������µĶ���
	Image new_img(img);

	//��ȡָ�������ڵ�ͼ��,����ʾ
	new_img.Cut(100, 100, 200, 200);
	new_img.Show("Cut_Image");

	//��תͼ����ʾ�����������ת�Ƕ�Ϊ90�ȵ���������
	img.Rotate(90);
	img.Show("Image");

	//��ͼ��ľ�ֵ�ͷ���������������
	float m = 0;
	float var = 0;
	img.Mean_Variance(m, var);
	cout << "��ֵ��" << m << endl;
	cout << "����" << var << endl;

	//��������ͼ�������
	Image img1("Baboon.jpg");
	Image img2("Lena.jpg");
	img1.Show("Image1");
	img2.Show("Image2");

	Swap(img1, img2);
	img1.Show("Image1");
	img2.Show("Image2");

	  return 0;
}

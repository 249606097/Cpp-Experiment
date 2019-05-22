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

	//上下翻转 img.Flip(true)
	img.Flip(true);
	img.Show("Image");

	// 左右翻转 img.Filp(false)
	img.Flip(false);
	img.Show("Image");

	// 图像放大 img.Resize(true)
	img.Resize(true);
	img.Show("Image");

	//图像缩小 img.Resize(false)
	img.Resize(false);
	img.Show("Image");

	//获取图像的某点的像素值,并修改
	cout << int(img.At(100, 100));
	img.Set(0, 100, 100);

    //使用拷贝构造函数创建新的对象
	Image new_img(img);

	//截取指定区域内的图像,并显示
	new_img.Cut(100, 100, 200, 200);
	new_img.Show("Cut_Image");

	//旋转图像并显示（简单起见，旋转角度为90度的整数倍）
	img.Rotate(90);
	img.Show("Image");

	//求图像的均值和方差，并在命令行输出
	float m = 0;
	float var = 0;
	img.Mean_Variance(m, var);
	cout << "均值：" << m << endl;
	cout << "方差" << var << endl;

	//交换两个图像的数据
	Image img1("Baboon.jpg");
	Image img2("Lena.jpg");
	img1.Show("Image1");
	img2.Show("Image2");

	Swap(img1, img2);
	img1.Show("Image1");
	img2.Show("Image2");

	  return 0;
}

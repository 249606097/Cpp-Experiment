#include "cv.h"
#include "highgui.h"
#include <iostream>

using namespace std;

void ReadImageData(unsigned char **dst, unsigned char *src, int rows, int cols, int width_step)
{
    int i;
    int j;

    for (i=0; i<rows; i++)
    {
        for (j=0; j<cols; j++)
        {
            dst[i][j] = src[width_step * i + j];
        }
    }

    return;
}

void WriteImageData(unsigned char *dst, unsigned char **src, int rows, int cols, int width_step)
{
    int i;
    int j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            dst[width_step * i + j] = src[i][j];
        }
    }

    return;
}

void FlipImageUpDown(unsigned char **d, int rows, int cols)
{
    int up_line = 0;
    int down_line = rows-1;

    while (up_line < down_line)
    {
        for (int j = 0; j < cols; j++)
        {
            unsigned char temp;
            temp = d[up_line][j];
            d[up_line][j] = d[down_line][j];
            d[down_line][j] = temp;
        }

        up_line++;
        down_line--;
    }

    return;
}

void FlipImageLeftRight(unsigned char **d, int rows, int cols)
{
    int left_line = 0;
    int right_line = cols - 1;

    while (left_line < right_line)
    {
        int i;
        for (i = 0 ; i < rows; i++)
        {
            unsigned char temp;
            temp = d[i][left_line];
            d[i][left_line] = d[i][right_line];
            d[i][right_line] = temp;
        }

        left_line++;
        right_line--;
    }

    return;
}

void ChangeImageHalf(unsigned char **b, unsigned char **a, int rows, int cols)
{
    int i;
    int j;

    for (i = 0; i < rows / 2; i++)
    {
        for (j = 0; j < cols / 2; j++)
        {
            b[i][j] = a[2*i][2*j];
        }
    }

    return;
}


int main(int argc, char* argv[])
{
	IplImage* img = cvLoadImage("Fruits.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
    cvShowImage("Image", img);
    cvWaitKey(0); //等待按键

    unsigned char *img_data = (unsigned char *)(img->imageData);
	int height = img->height;
	int width = img->width;
	int width_step = img->widthStep;

    int i;
    // 动态分配二维数组a，大小是height*width，unsigned char类型;
    unsigned char **a;                  
    a = new unsigned char *[height];
    for (i = 0; i < height; i++)
        a[i] = new unsigned char [width];

	// 读取图像数据到二维数组a中，实现函数ReadImageData
    ReadImageData(a, img_data, height, width, width_step);
    
    

    cout << "/****数组操作****/" << endl;
    cout << "请选择相应操作：" << endl;
    cout << "“1”：上下翻转图像；" << endl;
    cout << "“2”：左右翻转图像；" << endl;
    cout << "“3”：缩小图像尺寸为原来的一半；" << endl;
    cout << "“4”：退出；" << endl;

    int choice;
    cin >> choice;
    switch (choice)
    {
        case 1: 
        // 上下翻转图像
        FlipImageUpDown(a, height, width);
        WriteImageData(img_data, a, height, width, width_step);

        cvShowImage("Image", img);
        cvWaitKey(0);break;

        case 2: 
        // 左右翻转图像
        FlipImageLeftRight(a, height, width);
        WriteImageData(img_data, a, height, width, width_step);

        cvShowImage("Image", img);
        cvWaitKey(0); break;

        case 3: 
        // 动态分配二维数组b，用来存储缩小后的图像
        unsigned char **b;                   
        b = new unsigned char *[height/2];
        for (i = 0; i < height / 2; i++)
            b[i] = new unsigned char [width/2];
                    
        // 将原图缩小为原尺寸的一半，结果存入b中，添加相应的函数实现
        ChangeImageHalf(b, a, height, width);

        IplImage *img2 = cvCreateImage(cvSize(width / 2, height / 2), IPL_DEPTH_8U, 1);
        WriteImageData((unsigned char*)(img2->imageData), b, img2->height, img2->width, img2->widthStep);
        cvShowImage("Image", img2);
        cvWaitKey(0);
        for (i=0; i<height/2; i++)
		    delete [] b[i];
	    delete [] b;
        cvReleaseImage(&img2);break;
    }

	// cout << "每行所占的字节数：" << width_step << endl;
	// cout << "列数*每个元素所占字节数" << width << endl;
	// if (width_step == width)
	// 	cout << "width_step == 列数*每个元素所占字节数" << endl;
	// else
	// 	cout << "width_step ！= 列数*每个元素所占字节数" << endl;

    // 释放窗口 图像
	cvDestroyWindow("Image");
	cvReleaseImage(&img);

    // 释放二维数组a的空间
	for (i=0; i<height; i++)
		delete [] a[i];
	delete [] a;

	return 0;
}

#ifndef IMAGE_H
#define IMAGE_H

#include "Matrix.h"

class Image: public Matrix
{
    public:
		Image() : Matrix() {};
		Image(int h, int w) : Matrix(h, w) {};
		Image(int h, int w, double val) : Matrix(h, w, val) {};
		Image(Matrix const &m) : Matrix(m) {};
		Image(char* ImageName);
        Image(const Image &im);
        virtual ~Image();
        
        void Read(char* ImageName); //从硬盘文件中读入图像数据;
        void Write(char* filename); //将图像数据保存为图像文件;
        void Show(char* winname); //显示图像;
        
        void Flip(int code); //图像的翻转; code为0左右，1 上下;
        void Resize(int h, int w); //图像的缩放为参数指定的大小
        void Cut(int x1,int y1,int x2,int y2);//裁剪点(x1,y1)到点(x2,y2)的图像
        void Rotate(int degree);//图像旋转的函数（旋转角度为任意角度）
        double Mean();//返回图像的均值
        double Variance();//求图像的方差

		Image operator-();  //对图像取反，把所有像素的值都规整到[0,1]之间，然后每个像素都被1.0减
		Image gray2bw(double t); //以给定阈值t对图像进行二值化，返回结果图像对象；

};

#endif

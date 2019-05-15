#ifndef IMAGE_H
#define IMAGE_H

#include "Matrix.h"

class Image: public Matrix
{
    public:
        Image(); //构造函数，创建行列都为零的Image对象
        Image(int h, int w); //构造函数重载，创建h行，w列的Image对象
        Image(int h, int w, unsigned char val); //构造函数重载，创建的图像像素值都为val;
        Image(char* ImageName); //构造函数重载，利用文件名从硬盘加载图像文件成为Image对象;
        Image(unsigned char m[][100], int n); //构造函数重载，从静态数组创建Image对象;
        Image(unsigned char **m, int h, int w); //构造函数重载，从动态数组创建Image对象;
        Image(const Matrix &m); //构造函数重载，由Matrix类对象构造Image类对象
        Image(const Image &im); //拷贝构造函数;
        virtual ~Image(); //析构函数;
        
        void Read(char* ImageName); //从硬盘文件中读入图像数据;
        void Write(char* filename); //将图像数据保存为图像文件;
        void Show(char* winname); //显示图像;
        
        void Flip(int code); //图像的翻转; code为0左右，1 上下;
        //void Resize(int h, int w); //图像的缩放为参数指定的大小
        void Cut(int x1,int y1,int x2,int y2);//裁剪点(x1,y1)到点(x2,y2)的图像
        void Rotate(int degree);//图像旋转的函数（旋转角度为任意角度）
        double Mean();//返回图像的均值
        double Variance();//求图像的方差
		void Reshape(int h, int w);

		void Cat(Image &m, int code);
		void Transpose();
		friend Matrix Add(const Image &m1, const Image &m2);
		friend Matrix Sub(const Image &m1, const Image &m2);

private:
		unsigned char **data;
};



//构造函数
Image::Image()
{
	this->height = 0;
	this->width = 0;
	this->data = NULL;
}

//构造函数重载
Image::Image(int h, int w)
{
	this->height = h;
	this->width = w;
	this->data = NULL;
}

Image::Image(int h, int w, unsigned char val)
{
	this->height = h;
	this->width = w;

	int i;
	int j;

	this->data = new unsigned char *[this->height];
	for (i = 0; i < this->height; i++)
		this->data[i] = new unsigned char[this->width];

	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			this->data[i][j] = val;
		}
	}
}

Image::Image(char* ImageName)
{
	IplImage* img = cvLoadImage(ImageName, CV_LOAD_IMAGE_GRAYSCALE);
	unsigned char *img_data = (unsigned char *)(img->imageData);

	this->height = img->height;
	this->width = img->width;

	int i;
	int j;

	this->data = new unsigned char *[this->height];
	for (i = 0; i < this->height; i++)
		this->data[i] = new unsigned char[this->width];

	for (i = 0; i < this->height; i++)
	{
		for (j = 0; j < this->width; j++)
		{
			this->data[i][j] = img_data[i*img->widthStep + j];
		}
	}

	cvReleaseImage(&img);
}

Image::Image(Matrix const &m)
{
	this->height = m.height;
	this->width = m.width;

	int i;
	int j;

	this->data = new unsigned char *[this->height];
	for (i = 0; i < this->height; i++)
		this->data[i] = new unsigned char[this->width];

	for (i = 0; i < this->height; i++)
		for (j = 0; j < this->width; j++)
		{
			this->data[i][j] = (unsigned char)m.data[i][j];
		}
}

Image::Image(unsigned char m[][100], int rows)
{
	this->height = rows;
	this->width = 100;

	int i;
	int j;

	this->data = new unsigned char *[this->height];
	for (i = 0; i < this->height; i++)
		this->data[i] = new unsigned char[this->width];

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < 100; j++)
		{
			this->data[i][j] = m[i][j];
		}
	}
}

Image::Image(unsigned char **m, int h, int w)
{
	this->height = h;
	this->width = w;

	int i;
	int j;

	this->data = new unsigned char *[this->height];
	for (i = 0; i < this->height; i++)
		this->data[i] = new unsigned char[this->width];

	for (i = 0; i < this->height; i++)
	{
		for (j = 0; j < this->width; j++)
		{
			this->data[i][j] = m[i][j];
		}
	}
}

Image::Image(const Image &im)
{
	this->height = im.height;
	this->width = im.width;

	int i;
	int j;

	this->data = new unsigned char *[this->height];
	for (i = 0; i < this->height; i++)
		this->data[i] = new unsigned char[this->width];


	for (i = 0; i < this->height; i++)
	{
		for (j = 0; j < this->width; j++)
		{
			this->data[i][j] = im.data[i][j];
		}
	}
}

Image::~Image()
{
	int i;

	for (i = 0; i < this->height; i++)
		delete[] this->data[i];
	delete[] this->data;
}

//从硬盘读入图像文件; 
void Image::Read(char* ImageName)
{
	IplImage* img = cvLoadImage(ImageName, CV_LOAD_IMAGE_GRAYSCALE);
	unsigned char *img_data = (unsigned char *)(img->imageData);
	int widthstep = img->widthStep;

	//将一维指针img_data指向的内存中的值写入成员变量二维指针data所指的内存中
	this->height = img->height;
	this->width = img->width;

	int i;
	int j;

	this->data = new unsigned char *[this->height];
	for (i = 0; i < this->height; i++)
		this->data[i] = new unsigned char[this->width];

	for (i = 0; i < this->height; i++)
	{
		for (j = 0; j < this->width; j++)
		{
			this->data[i][j] = img_data[i*img->widthStep + j];
		}
	}

	cvReleaseImage(&img);
}

//保存图像; 
void Image::Write(char *filename)
{
	IplImage* img = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	unsigned char *img_data = (unsigned char *)(img->imageData);
	int widthstep = img->widthStep;

	//将成员变量二维指针data所指内存中的值写入一维指针img_data所指的内存
	int i;
	int j;

	for (i = 0; i < this->height; i++)
	{
		for (j = 0; j < this->width; j++)
		{
			img_data[i*widthstep + j] = this->data[i][j];
		}
	}

	cvSaveImage(filename, img);
	cvReleaseImage(&img);
}

//显示图像;
void Image::Show(char *winname)
{
	IplImage *img = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	unsigned char *img_data = (unsigned char *)(img->imageData);
	int widthstep = img->widthStep;

	//将data所指内存中的值写入img_data所指的内存
	int i;
	int j;

	for (i = 0; i < this->height; i++)
	{
		for (j = 0; j < this->width; j++)
		{
			img_data[i*widthstep + j] = this->data[i][j];
		}
	}

	cvNamedWindow(winname, CV_WINDOW_AUTOSIZE);//创建窗口
	cvShowImage(winname, img);
	cvWaitKey(0);
	cvReleaseImage(&img); //释放图像;
}

//false 左右，true 上下;
void Image::Flip(int code)
{
	if (code)
	{
		int up_line = 0;
		int down_line = this->height - 1;
		int j;
		unsigned char temp;

		while (up_line < down_line)
		{
			for (j = 0; j < this->width; j++)
			{
				temp = this->data[up_line][j];
				this->data[up_line][j] = this->data[down_line][j];
				this->data[down_line][j] = temp;
			}

			up_line++;
			down_line--;
		}
	}
	else
	{
		int left_line = 0;
		int right_line = this->width - 1;
		int i;
		unsigned char temp;

		while (left_line < right_line)
		{
			for (i = 0; i < this->height; i++)
			{
				temp = this->data[i][left_line];
				this->data[i][left_line] = this->data[i][right_line];
				this->data[i][right_line] = temp;
			}

			left_line++;
			right_line--;
		}
	}
}

/*
//图像缩小，放大
void Image::Resize(int code)
{
if (code)
{
int i;
int j;

unsigned char **original_data = this->data;

this->data = new unsigned char *[this->height * 2];
for (i = 0; i < this->height * 2; i++)
this->data[i] = new unsigned char[this->width * 2];

for (i = 0; i < this->height * 2; i++)
{
for (j = 0; j < this->width * 2; j++)
{
unsigned char temp;

int original_i = i / 2;
int original_j = j / 2;

// 越界 处理
if (i / 2 + 1 >= this->height)
{
original_i = this->height - 1 - 1;
}
if (j / 2 + 1 >= this->width)
{
original_j = this->width - 1 - 1;
}
if (i / 2 + 1 >= this->height && j / 2 + 1 >= this->width)
{
original_i = this->height - 1 - 1;
original_j = this->width - 1 - 1;
}

// 偶数行 奇数列
if (i % 2 != 0 && j % 2 == 0)
{
temp = (original_data[i / 2][j / 2] + original_data[original_i + 1][j / 2]) / 2;
}

// 奇数行 偶数列
if (i % 2 == 0 && j % 2 != 0)
{
temp = (original_data[i / 2][j / 2] + original_data[i / 2][original_j + 1]) / 2;
}

// 偶数行 偶数列
if (i % 2 != 0 && j % 2 != 0)
{
temp = (original_data[i / 2][j / 2] + original_data[i / 2][original_j + 1] + original_data[i / 2][j / 2] + original_data[original_i + 1][j / 2]) / 4;
}

// 奇数行 奇数列
if (i % 2 == 0 && j % 2 == 0)
{
temp = original_data[i / 2][j / 2];
}



this->data[i][j] = temp;
}
}

this->height *= 2;
this->width *= 2;

for (i = 0; i < this->height / 2; i++)
delete[] original_data[i];
delete[] original_data;
}
else
{
int i;
int j;

unsigned char **original_data = this->data;

this->data = new unsigned char *[this->height / 2];
for (i = 0; i < this->height / 2; i++)
this->data[i] = new unsigned char[this->width / 2];

for (i = 0; i < this->height / 2; i++)
{
for (j = 0; j < this->width / 2; j++)
{
this->data[i][j] = original_data[2 * i][2 * j];
}
}

this->height /= 2;
this->width /= 2;

for (i = 0; i < this->height * 2; i++)
delete[] original_data[i];
delete[] original_data;
}
}
*/

void Image::Cut(int x1, int y1, int x2, int y2)
{
	int i;
	int j;

	unsigned char **original_data = this->data;

	this->data = new unsigned char *[abs(x1 - x2) + 1];
	for (i = 0; i < abs(x1 - x2) + 1; i++)
		this->data[i] = new unsigned char[abs(y1 - y2) + 1];

	for (i = 0; i < abs(x1 - x2) + 1; i++)
	{
		for (j = 0; j < abs(y1 - y2) + 1; j++)
		{
			this->data[i][j] = original_data[x1 + i][y1 + j];
		}
	}

	for (i = 0; i < this->height; i++)
		delete[] original_data[i];
	delete[] original_data;

	this->height = abs(x1 - x2) + 1;
	this->width = abs(y1 - y2) + 1;
}

void Image::Rotate(int degree)
{
	while (degree < 0)
		degree += 360;

	degree = degree % 360;

	int num = degree / 90;

	switch (num)
	{
	case 0:
		break;
	case 1:
	{
		int i;
		int j;

		unsigned char **original_data = this->data;

		this->data = new unsigned char *[this->width];
		for (i = 0; i < this->width; i++)
			this->data[i] = new unsigned char[this->height];

		for (i = 0; i < this->height; i++)
		{
			for (j = 0; j < this->width; j++)
			{
				this->data[j][i] = original_data[i][j];
			}
		}

		int temp;
		temp = this->height;
		this->height = this->width;
		this->width = temp;
	}
	break;
	case 2:
	{
		int i;
		int j;

		unsigned char **original_data = this->data;

		this->data = new unsigned char *[this->height];
		for (i = 0; i < this->height; i++)
			this->data[i] = new unsigned char[this->width];

		for (i = 0; i < this->height; i++)
		{
			for (j = 0; j < this->width; j++)
			{
				this->data[this->height - 1 - i][this->width - 1 - j] = original_data[i][j];
			}
		}
	}
	break;
	case 3:
	{
		int i;
		int j;

		unsigned char **original_data = this->data;

		this->data = new unsigned char *[this->width];
		for (i = 0; i < this->width; i++)
			this->data[i] = new unsigned char[this->height];

		for (i = 0; i < this->height; i++)
		{
			for (j = 0; j < this->width; j++)
			{
				this->data[j][this->height - 1 - i] = original_data[i][j];
			}
		}

		int temp;
		temp = this->height;
		this->height = this->width;
		this->width = temp;
	}
	break;
	}
}

double Image::Mean()
{
	double mean = 0;

	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			mean += this->data[i][j];
		}
	}
	mean /= this->height * this->width;

	return mean;
}

double Image::Variance()
{
	double mean = Mean();
	double var = 0;

	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			var += (mean - this->data[i][j]) * (mean - this->data[i][j]);
		}
	}
	var /= this->height * this->width;

	return var;
}


void Image::Reshape(int h, int w) //在矩阵元素总数不变的情况下，将矩阵行列变为参数给定的大小
{
	if (this->height * this->width != h * w)
	{
		cout << "error" << endl;
		return;
	}

	unsigned char** origin = this->data;
	int origin_h = this->height;
	int origin_w = this->width;

	this->height = h;
	this->width = w;

	int i;
	int j;

	this->data = new unsigned char *[this->height];
	for (i = 0; i < this->height; i++)
		this->data[i] = new unsigned char[this->width];

	for (i = 0; i < origin_h; i++)
		for (j = 0; j < origin_w; j++)
		{
			this->data[(origin_w * i + j) / this->width][(origin_w * i + j) - ((origin_w * i + j) / this->width * this->width)] = origin[i][j];
		}

	for (i = 0; i < origin_h; i++)
	{
		delete[] origin[i];
	}
	delete[] origin;
}

Matrix Add(const Image &m1, const Image &m2) // 友元函数，将矩阵m1和m2相加，结果矩阵作为函数的返回值
{
	if (m1.height != m2.height || m1.width != m2.width)
	{
		Matrix m;
		cout << "error" << endl;
		return m;
	}

	Matrix m(m1.height, m1.width);
	for (int i = 0; i < m1.height; i++)
		for (int j = 0; j < m1.width; j++)
		{
			if (m1.data[i][j] + m2.data[i][j] > 255)
			{
				m.data[i][j] = 255;
				continue;
			}

			m.data[i][j] = m1.data[i][j] + m2.data[i][j];
		}

	return m;
}

Matrix Sub(const Image &m1, const Image &m2) // 友元函数，将矩阵m1和m2相减，结果矩阵作为函数的返回值
{

	if (m1.height != m2.height || m1.width != m2.width)
	{
		Matrix m;
		cout << "error" << endl;
		return m;
	}

	Matrix m(m1.height, m1.width);
	for (int i = 0; i < m1.height; i++)
		for (int j = 0; j < m1.width; j++)
		{
			if (m1.data[i][j] - m2.data[i][j] < 0)
			{
				m.data[i][j] = 0;
				continue;
			}

			m.data[i][j] = m1.data[i][j] - m2.data[i][j];
		}

	return m;
}

void Image::Transpose() // 将矩阵转置
{
	unsigned char** origin = this->data;

	int i;
	int j;

	int origin_h = this->height;
	int origin_w = this->width;

	this->height = origin_w;
	this->width = origin_h;

	this->data = new unsigned char *[this->height];
	for (i = 0; i < this->height; i++)
		this->data[i] = new unsigned char[this->width];

	for (i = 0; i < this->height; i++)
		for (j = 0; j < this->width; j++)
		{
			this->data[i][j] = origin[j][i];
		}

	for (i = 0; i < this->width; i++)
		delete[] origin[i];
	delete[] origin;
}

void Image::Cat(Image &m, int code) // 将矩阵m与当前矩阵进行拼接，code代表拼接的方式：将m拼接到当前矩阵的上、下、左、右，具体例子见本大纲后面的说明
{
	if (code == 1)
	{
		if (this->height != m.height)
		{
			cout << "error" << endl;
			return;
		}

		unsigned char** origin = this->data;
		int origin_h = this->height;
		int origin_w = this->width;

		int i;
		int j;

		this->height = origin_h;
		this->width = origin_w + m.width;

		this->data = new unsigned char *[this->height];
		for (i = 0; i < this->height; i++)
			this->data[i] = new unsigned char[this->width];

		for (i = 0; i < origin_h; i++)
			for (j = 0; j < origin_w; j++)
			{
				this->data[i][j] = origin[i][j];
			}

		for (i = 0; i < origin_h; i++)
			for (j = origin_w; j < origin_w + m.width; j++)
			{
				this->data[i][j] = m.data[i][j - m.width];
			}

		for (i = 0; i < origin_h; i++)
			delete[] origin[i];
		delete[] origin;
	}

	if (code == 2)
	{
		if (this->width != m.width)
		{
			cout << "error" << endl;
			return;
		}

		unsigned char** origin = this->data;
		int origin_h = this->height;
		int origin_w = this->width;

		int i;
		int j;

		this->height = origin_h + m.height;
		this->width = origin_w;

		this->data = new unsigned char *[this->height];
		for (i = 0; i < this->height; i++)
			this->data[i] = new unsigned char[this->width];

		for (i = 0; i < origin_h; i++)
			for (j = 0; j < origin_w; j++)
			{
				this->data[i][j] = origin[i][j];
			}

		for (i = origin_h; i < origin_h + m.height; i++)
			for (j = 0; j < origin_w; j++)
			{
				this->data[i][j] = m.data[i - origin_h][j];
			}
	}
}

#endif

#include "Image.h"

Image::Image(char* ImageName)
{
	IplImage* img = cvLoadImage(ImageName, CV_LOAD_IMAGE_GRAYSCALE);
	unsigned char *img_data = (unsigned char *)(img->imageData);

	this->init(img->height, img->width);

	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			this->data[i][j] = (double)img_data[i*img->widthStep + j];
		}
	}

	cvReleaseImage(&img);
}

Image::Image(const Image &im)
{
	this->init(im.height, im.width);

	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			this->data[i][j] = im.data[i][j];
		}
	}
}

Image::~Image()
{

}

//从硬盘读入图像文件; 
void Image::Read(char* ImageName)
{
	IplImage* img = cvLoadImage(ImageName, CV_LOAD_IMAGE_GRAYSCALE);
	unsigned char *img_data = (unsigned char *)(img->imageData);
	int widthstep = img->widthStep;

	this->init(img->height, img->width);

	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			this->data[i][j] = (double)img_data[i*img->widthStep + j];
		}
	}

	cvReleaseImage(&img);
}

//保存图像; 
void Image::Write(char *filename)
{
	IplImage* img = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	double *img_data = (double *)(img->imageData);
	int widthstep = img->widthStep;

	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
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
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			img_data[i*widthstep + j] = (unsigned char)this->data[i][j];
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

	double **original_data = this->data;

	this->data = new double *[abs(x1 - x2) + 1];
	for (i = 0; i < abs(x1 - x2) + 1; i++)
		this->data[i] = new double[abs(y1 - y2) + 1];

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

		double **original_data = this->data;

		this->data = new double *[this->width];
		for (i = 0; i < this->width; i++)
			this->data[i] = new double[this->height];

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

		double**original_data = this->data;

		this->data = new double *[this->height];
		for (i = 0; i < this->height; i++)
			this->data[i] = new double[this->width];

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

		double **original_data = this->data;

		this->data = new double *[this->width];
		for (i = 0; i < this->width; i++)
			this->data[i] = new double[this->height];

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
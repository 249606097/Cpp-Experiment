#include "cv.h"
#include "highgui.h"
#include "Image.h"

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
		this->data[i] = new unsigned char [this->width];

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
		this->data[i] = new unsigned char [this->width];
	
	for (i = 0; i < this->height; i++)
	{
		for (j = 0; j < this->width; j++)
		{
			this->data[i][j] = img_data[i*img->widthStep + j];
		}
	}

	cvReleaseImage(&img);
}

Image::Image(unsigned char *m, int rows, int cols)
{
	this->height = rows;
	this->width = cols;

	int i;
	int j;

	this->data = new unsigned char *[this->height];
	for (i = 0; i < this->height; i++)
		this->data[i] = new unsigned char [this->width];

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			this->data[i][j] = m[i*cols + j];
		}
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
		this->data[i] = new unsigned char [this->width];

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
		this->data[i] = new unsigned char [this->width];

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
		this->data[i] = new unsigned char [this->width];

	
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
		delete [] this->data[i];
	delete [] this->data;
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
		this->data[i] = new unsigned char [this->width];
	
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

//获取图像中指定点的值
unsigned char& Image::At(int row, int col)
{
    return this->data[row][col];
}

void Image::Set(int row, int col, unsigned char value)
{
	this->data[row][col] = value;
}

//设置图像为同一值
void Image::Set(unsigned char value)
{
    int i;
	int j;

	for (i = 0; i < this->height; i++)
	{
		for (j = 0; j < this->width; j++)
		{
			this->data[i][j] = value;
		}
	}
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

//图像缩小，放大
void Image::Resize(int code)
{
    if (code)
	{
		int i;
		int j;

		unsigned char **original_data = this->data;

		this->data = new unsigned char *[this->height*2];
		for (i = 0; i < this->height*2; i++)
			this->data[i] = new unsigned char [this->width*2];

		for (i = 0; i < this->height*2; i++)
		{
			for (j = 0; j < this->width*2; j++)
			{
				unsigned char temp;

				int original_i = i / 2;
				int original_j = j / 2;

				// 越界 处理
				if (i / 2 + 1 >= this->height)
				{
					original_i =this->height-1 -1;
				}
				if (j / 2 + 1 >= this->width)
				{
					original_j = this->width-1 -1;
				}
				if (i / 2 + 1 >= this->height && j / 2 + 1 >= this->width)
				{
					original_i =this->height-1 -1;
					original_j = this->width-1 -1;
				}

				// 偶数行 奇数列
				if (i % 2 != 0 && j % 2 ==0)
				{
					temp = (original_data[i/2][j/2] + original_data[original_i+1][j/2]) / 2;
				}

				// 奇数行 偶数列
				if (i % 2 == 0 && j % 2 != 0)
				{
					temp = (original_data[i/2][j/2] + original_data[i/2][original_j+1]) / 2;
				}

				// 偶数行 偶数列
				if (i % 2 != 0 && j % 2 != 0)
				{
					temp = (original_data[i/2][j/2] + original_data[i/2][original_j+1] + original_data[i/2][j/2] + original_data[original_i+1][j/2]) / 4;
				}

				// 奇数行 奇数列
				if (i % 2 == 0 && j % 2 == 0)
				{
					temp = original_data[i/2][j/2];
				}

				

				this->data[i][j] = temp;
			}
		}

		this->height *= 2;
		this->width *= 2;

		for (i = 0; i < this->height/2; i++)
			delete [] original_data[i];
		delete [] original_data;
	}
	else
	{
		int i;
		int j;

		unsigned char **original_data = this->data;
		
		this->data = new unsigned char *[this->height/2];
		for (i = 0; i < this->height/2; i++)
			this->data[i] = new unsigned char [this->width/2];
		
		for (i = 0; i < this->height/2; i++)
		{
			for (j =0; j < this->width/2; j++)
			{
				this->data[i][j] = original_data[2*i][2*j];
			}
		}

		this->height /= 2;
		this->width /= 2;

		for (i = 0; i < this->height*2; i++)
			delete [] original_data[i];
		delete [] original_data;
	}
}

void Image::Cut(int x1,int y1,int x2,int y2)
{
	int i;
	int j;

	unsigned char **original_data = this->data;

	this->data = new unsigned char *[abs(x1 - x2) + 1];
	for (i = 0; i < abs(x1 - x2) + 1; i++)
		this->data[i] = new unsigned char [abs(y1 - y2) + 1];

	for (i = 0; i < abs(x1 - x2) + 1; i++)
	{
		for (j = 0; j < abs(y1 - y2) + 1; j++)
		{
			this->data[i][j] = original_data[x1 + i][y1 + j];
		}
	}

	for (i = 0; i < this->height; i++)
		delete [] original_data[i];
	delete [] original_data;

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
					this->data[i] = new unsigned char [this->height];

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
					this->data[i] = new unsigned char [this->width];

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
					this->data[i] = new unsigned char [this->height];

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

void Image::Mean_Variance(float &m, float &var)
{
	int i;
	int j;

	for (i = 0; i < this->height; i++)
	{
		for (j =0 ; j < this->width; j++)
		{
			m += this->data[i][j];
		}
	}
	m /= this->height * this->width;

	for (i = 0; i < this->height; i++)
	{
		for (j =0 ; j < this->width; j++)
		{
			var += (m - this->data[i][j]) * (m - this->data[i][j]);
		}
	}
	var /= this->height * this->width;
}

//实现友元函数，交换两个Image对象的数据
void Swap(Image &a, Image &b)
{
	unsigned char temp;

	for (int i = 0; i < a.height; i++)
	{
		for (int j = 0; j < a.width; j++)
		{
			temp = a.data[i][j];
			a.data[i][j] = b.data[i][j];
			b.data[i][j] = temp;
		}
	}
}

#include <cstdlib>
#include <iostream>
#include <ctime>
#include "cv.h"
#include "highgui.h"

using namespace std;

void DrawPixel(IplImage *img, int row, int col, unsigned char v);
void DrawAll(IplImage *img, int height, int width, unsigned char v);
unsigned char GetPixel(IplImage *img, int row, int col);
void DrawCircle(IplImage *img, int height, int width, int row, int col, int radius, unsigned char v);
bool in_circle(int x, int y);

int main()
{

	int width=1000;
	int height=1000;
	IplImage* img = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	
    DrawAll(img, height, width, 0);
	DrawCircle(img, height, width, 500, 500, 500, '255');

	cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
    cvShowImage("Image", img);
    cvWaitKey(0);


	srand(time(0));

	double e = 0.01;
	int n=1000;
	double pi = 100.0;
	double residual = 100;
	int count = 0;

	while (residual > e)
	{
		int m =0;
		for (int i =0; i < n; i++)
		{
			int a;
			int b;
			for (a=0; a<height; a++)
			{
				for (b=0; b<width; b++)
				{
					unsigned char now = GetPixel(img, a, b);
					if (now != 0)
					{	
						now -= 1;
						DrawPixel(img, a, b, now);
					}
				}
			}
			
			
			int x = int(double(rand())/double(RAND_MAX)*width);
			int y = int(double(rand())/double(RAND_MAX)*height);
			
			DrawPixel(img, x, y, 255);
			DrawCircle(img, height, width, 500, 500, 500, '255');
			cvShowImage("Image", img);
			cvWaitKey(1);

			if (in_circle(x, y))
				m += 1;
			
		}
		residual = fabs(pi - 4.0 * double(m) / double (n));
		if (count == 0)
        {
            pi = 4.0 * double(m) / double(n);
        }
        else
        {
            pi = (pi * count + 4.0 * double(m) / double(n)) / (count + 1);
        }
        count++;
		cout << "产生的点数：" << i << "\t落入圆内的个数：" << m << endl;
		cout << "pi 的值：" << pi << endl;
	}

	cvWaitKey(0); 
    cvDestroyWindow("Image");
    cvReleaseImage(&img); 

	return 0;
}


void DrawAll(IplImage *img, int height, int width, unsigned char v)
{
	int i;
	int j;

	for (i=height;i>0;i--)
    {
        for (j=width;j>0;j--)
        {
            DrawPixel(img, i, j, v);
        }
    }

    return;
}

void DrawPixel(IplImage *img, int row, int col, unsigned char v)
{
	unsigned char *img_data = (unsigned char *)(img->imageData);
	int width_step = img->widthStep;
	img_data[width_step * row + col] = v;
}

unsigned char GetPixel(IplImage *img, int row, int col)
{
    unsigned char *img_data = (unsigned char *)(img->imageData);
    int width_step = img->widthStep;
    return img_data[width_step * row + col];
}

void DrawCircle(IplImage *img, int height, int width, int row, int col, int radius, unsigned char v)
{
	int i;
	int j;
	for (i=height;i>0;i--)
		for (j=width;j>0;j--)
		{
			if ( fabs(((double (i)-row)*(double (i)-row)+(double (j)-col)*(double (j)-col) - double(radius)*radius)) < 500)
				DrawPixel(img, i, j, 255);
		}
}

bool in_circle(int x, int y)
{
	if ((x-500)*(x-500) + (y-500)*(y-500) < 500 * 500)
		return true;
	else
		return false;
}
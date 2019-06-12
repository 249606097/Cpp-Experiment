#ifndef MAT_HPP
#define MAT_HPP

#include "highgui.h"
#include <iostream>

using namespace std;

template<typename T>
class Proxy
{
public:
	Proxy(int h, int w)
	{
		this->height = h;
		this->width = w;
		this->referred_count = 1;

		if (this->height == 0 || this->width == 0)
		{
			this->data = NULL;
		}
		else
		{
			this->data = new T*[this->height];
			for (int i = 0; i < this->height; i++)
			{
				this->data[i] = new T[this->width];
			}
		}
	}

	~Proxy()
	{
		for (int i = 0; i < this->height; i++)
		{
			delete[] this->data[i];
		}
		delete[] this->data;
	}

public:
	T** data;
	int height;
	int width;
	int referred_count;
};


template<typename T>
class Mat
{
public:
	Mat(); //�޲����Ĺ��캯�����������ж�Ϊ���Mat����
	Mat(int h, int w); //���캯�����أ�����h�У�w�е�Mat����
	Mat(int h, int w, T val); //���캯�����أ�����Ԫ�ص�ֵ��Ϊval;
	Mat(char* ImageName); //���캯�����أ������ļ�����Ӳ�̼���ͼ���ļ���ΪMat����;
	Mat(T **m, int h, int w); //���캯�����أ��Ӷ�̬���鴴��Mat����;
	Mat(const Mat &m); //�������캯��;
	virtual ~Mat(); //��������;

	void Read(const char *ImageName); //��Ӳ���ļ��ж���ͼ������;
	void Write(const char *filename); //�����ݱ���Ϊͼ���ļ�;
	void Show(const char *winname); //��ͼ������ʾ����;
	
	int Height();//�õ�����߶�
	int Height() const;//�õ�����߶�
	int Width();//�õ�������
	int Width() const;//�õ�������
					  
	T Min(); //�õ�����Ԫ�ص���Сֵ
	T Min() const; //�õ�����Ԫ�ص���Сֵ
	T Max(); //�õ�����Ԫ�ص����ֵ
	T Max() const; //�õ�����Ԫ�ص����ֵ
				   
	T& At(int row, int col);          //��ȡĳ���ֵ
	T& At(int row, int col) const;  //��ȡĳ���ֵ��const����
	void Set(int row, int col, T value); //����Ԫ��(row,col)Ϊĳֵ;
	void Set(T value); //��������Ԫ��Ϊͬһֵ;
	
	void Flip(int code); //��ת; ����code��ֵ��0:���ҷ�ת��1:���·�ת; 
	void Resize(int h, int w); //����
	void Cut(int x1, int y1, int x2, int y2);//�ü���(x1,y1)����(x2,y2)
	void Rotate(int degree);//��ת
	void Transpose(); // ת��
	void Reshape(int h, int w); //��Ԫ���������������£�����������б�Ϊ���������Ĵ�С
	bool IsEmpty();// �ж��Ƿ�Ϊ�վ���
	bool IsSquare();// �жϾ����Ƿ�Ϊ����
	Mat<T>  MajorDiagonal();// �����Խ����ϵ�Ԫ�أ����һ��N��1�еľ���NΪ���Խ�����Ԫ�صĸ���
	Mat<T>  MinorDiagonal();// �󸱶Խ����ϵ�Ԫ�أ����һ��N��1�еľ���NΪ���Խ�����Ԫ�صĸ���
	Mat<T> Row(int n);// ���ؾ���ĵ�n���ϵ�Ԫ�أ����һ��1��N�еľ��������NΪ��n����Ԫ�صĸ���
	Mat<T> Column(int n);// ���ؾ���ĵ�n���ϵ�Ԫ�أ����һ��N��1�еľ��������NΪ��n����Ԫ�صĸ���
	void Cat(Mat<T> &m, int code); // ��m�뵱ǰ�������ƴ�ӣ�code����ƴ�ӵķ�ʽ
	void CopyTo(Mat<T> &m); // �������Ƹ�m
							
	void Normalize();//������Ԫ�ص�ֵ�任��0-1��Χ�ڣ���double���͵�Mat���������ע�⣺�����������޷�����Mat<double>���͵Ķ����˽�г�Աdata����Ҫ������At�������ĳ��Ԫ�ء�
	
	Mat<T>& operator=(const Mat<T> &m);  //���ظ�ֵ���������ɶ����Ŀ�����
	bool operator==(const Mat<T> &m);  //�ж�����Mat�����Ƿ����
	


	friend Mat<T> operator+(const Mat<T> &lhs, const Mat<T> &rhs)  //��ӦԪ�ص���ֵ��ӣ�
	{
		Mat<T> temp(lhs.p->height, lhs.p->width);

		for (int i = 0; i < temp.p->height; i++)
		{
			for (int j = 0; j < temp.p->width; j++)
			{
				temp.p->data[i][j] = lhs.p->data[i][j] + rhs.p->data[i][j];
			}
		}

		return temp;
	}

	friend Mat<T> operator-(const Mat<T> &lhs, const Mat<T> &rhs)  //��ӦԪ�ص���ֵ�����
	{

		Mat<T> temp(lhs.p->height, lhs.p->width);

		for (int i = 0; i < temp.p->height; i++)
		{
			for (int j = 0; j < temp.p->width; j++)
			{
				temp.p->data[i][j] = lhs.p->data[i][j] - rhs.p->data[i][j];
			}
		}

		return temp;
	}



	Mat<T>& operator++();  //ǰ���Լӣ�
	Mat<T>& operator--();  //ǰ���Լ���
	Mat<T> operator ++(int);  //�����Լӣ�
	Mat<T> operator --(int);  //�����Լ���

	Mat<double> operator-();  // ȡ����ע��Ҫ�Ѿ�������ݹ�����[0,1]���������1��
		


	friend Mat<T> operator+(Mat<T> &m, T num) //����Ԫ�ؼ���ͬһ��ֵ;
	{
		Mat<T> temp(m.p->height, m.p->width);

		for (int i = 0; i < temp.p->height; i++)
		{
			for (int j = 0; j < temp.p->width; j++)
			{
				temp.p->data[i][j] = m.p->data[i][j] + num;
			}
		}

		return temp;
	}

	friend Mat<T> operator-(Mat<T> &m, T num) //����Ԫ�ؼ�ȥͬһ��ֵ;
	{
		return m + (-num);
	}

	friend Mat<T> operator*(Mat<T> &m, T num) //����Ԫ�س���ͬһ��ֵ;
	{
		Mat<T> temp(m.p->height, m.p->width);

		for (int i = 0; i < temp.p->height; i++)
		{
			for (int j = 0; j < temp.p->width; j++)
			{
				temp.p->data[i][j] = m.p->data[i][j] * num;
			}
		}

		return temp;
	}

	friend Mat<T> operator/(Mat<T> &m, T num) //����Ԫ�س���ͬһ��ֵ;
	{
		Mat<T> temp(m.p->height, m.p->width);

		for (int i = 0; i < temp.p->height; i++)
		{
			for (int j = 0; j < temp.p->width; j++)
			{
				temp.p->data[i][j] = m.p->data[i][j] / num;
			}
		}

		return temp;
	}
											   //���⣬����Ԫ������д��һ��T���͵�����һ��Mat����ļ�,��,��,��
	friend Mat<T> operator+(T num, Mat<T> &m)
	{
		return m + num;
	}

	friend Mat<T> operator-(T num, Mat<T> &m)
	{
		Mat<T> temp(m.p->height, m.p->width);

		for (int i = 0; i < temp.p->height; i++)
		{
			for (int j = 0; j < temp.p->width; j++)
			{
				temp.p->data[i][j] = num - m.p->data[i][j];
			}
		}

		return temp;
	}

	friend Mat<T> operator*(T num, Mat<T> &m)
	{
		return m * num;
	}

	friend Mat<T> operator/(T num, Mat<T> &m)
	{
		Mat<T> temp(m.p->height, m.p->width);

		for (int i = 0; i < temp.p->height; i++)
		{
			for (int j = 0; j < temp.p->width; j++)
			{
				temp.p->data[i][j] = num / m.p->data[i][j];
			}
		}

		return temp;
	}



	Mat<T> gray2bw(T t); //�Ը�����ֵt���ж�ֵ�������ؽ������



	friend void Swap(Mat<T> &a, Mat<T> &b)//ʹ����Ԫ������������Mat����
	{
		Proxy<T>* temp;

		temp = a.p;
		a.p = b.p;
		b.p = temp;
	}
	
private:
	Proxy<T>* p;
	// �Լ�ʵ��һ�������࣬�������������������������ü���������ָ��
	// ������Ҫ����ָ�����������ָ����Ϊ���ݳ�Ա
};

template<typename T>
Mat<T>::Mat()
{
	this->p = new Proxy<T>(0, 0);
}

template<typename T>
Mat<T>::Mat(int h, int w)
{
	this->p = new Proxy<T>(h, w);
}

template<typename T>
Mat<T>::Mat(int h, int w, T val)
{
	this->p = new Proxy<T>(h, w);

	for (int i = 0; i < this->p->height, i++)
	{
		for (int j = 0; j < this->p->width; j++)
		{
			this->p->data[i][j] = val;
		}
	}
}

template<typename T>
Mat<T>::Mat(char* ImageName)
{
	IplImage* img = cvLoadImage(ImageName, CV_LOAD_IMAGE_GRAYSCALE);
	unsigned char *img_data = (unsigned char *)(img->imageData);
	int widthstep = img->widthStep;

	this->p = new Proxy<T>(img->height, img->width);

	for (int i = 0; i < this->p->height; i++)
	{
		for (int j = 0; j < this->p->width; j++)
		{
			this->p->data[i][j] = (T)img_data[i*img->widthStep + j];
		}
	}

	cvReleaseImage(&img);
}

template<typename T>
Mat<T>::Mat(T **m, int h, int w)
{
	this->p = new Proxy(h, w);

	for (int i = 0; i < this->p->height, i++)
	{
		for (int j = 0; j < this->p->width; j++)
		{
			this->p->data[i][j] = m[i][j];
		}
	}
}

template<typename T>
Mat<T>::Mat(const Mat &m)
{
	this->p = m.p;
	++p->referred_count;
}

template<typename T>
Mat<T>::~Mat()
{
	if (--this->p->referred_count == 0)
		delete this->p;
}

template<typename T>
void Mat<T>::Read(const char *ImageName)
{
	IplImage* img = cvLoadImage(ImageName, CV_LOAD_IMAGE_GRAYSCALE);
	unsigned char *img_data = (unsigned char *)(img->imageData);
	int widthstep = img->widthStep;

	this->p = new Proxy<T>(img->height, img->width);

	for (int i = 0; i < this->p->height; i++)
	{
		for (int j = 0; j < this->p->width; j++)
		{
			this->p->data[i][j] = (T)img_data[i*img->widthStep + j];
		}
	}

	cvReleaseImage(&img);
}

template<typename T>
void Mat<T>::Write(const char *filename)
{
	IplImage* img = cvCreateImage(cvSize(this->p->width, this->p->height), IPL_DEPTH_8U, 1);
	unsigned char *img_data = (unsigned char *)(img->imageData);
	int widthstep = img->widthStep;

	for (int i = 0; i < this->p->height; i++)
	{
		for (int j = 0; j < this->p->width; j++)
		{
			img_data[i*widthstep + j] = this->p->data[i][j];
		}
	}

	cvSaveImage(filename, img);
	cvReleaseImage(&img);
}

template<typename T>
void Mat<T>::Show(const char *winname)
{
	IplImage *img = cvCreateImage(cvSize(this->p->width, this->p->height), IPL_DEPTH_8U, 1);
	unsigned char *img_data = (unsigned char *)(img->imageData);
	int widthstep = img->widthStep;

	//��data��ָ�ڴ��е�ֵд��img_data��ָ���ڴ�
	for (int i = 0; i < this->p->height; i++)
	{
		for (int j = 0; j < this->p->width; j++)
		{
			if (this->p->data[i][j] < 1)
			{
				img_data[i*widthstep + j] = 0;
				continue;
			}
			if (this->p->data[i][j] > 254)
			{
				img_data[i*widthstep + j] = 255;
				continue;
			}
			img_data[i*widthstep + j] = this->p->data[i][j];
		}
	}

	cvNamedWindow(winname, CV_WINDOW_AUTOSIZE);//��������
	cvShowImage(winname, img);
	cvWaitKey(0);
	cvReleaseImage(&img); //�ͷ�ͼ��;
}

template<typename T>
int Mat<T>::Height()
{
	return this->p->height;
}

template<typename T>
int Mat<T>::Height() const
{
	return this->p->height;
}

template<typename T>
int Mat<T>::Width()
{
	return this->p->width;
}

template<typename T>
int Mat<T>::Width() const
{
	return this->p->width;
}

template<typename T>
T Mat<T>::Min()
{
	T min = this->p->data[0][0];
	for (int i = 0; i < this->p->height; i++)
	{
		for (int j = 0; j < this->p->width; j++)
		{
			if (min > this->p->data[i][j])
			{
				min = this->p->data[i][j];
			}
		}
	}

	return min;
}

template<typename T>
T Mat<T>::Min() const
{
	T min = this->p->data[0][0];
	for (int i = 0; i < this->p->height; i++)
	{
		for (int j = 0; j < this->p->width; j++)
		{
			if (min > this->p->data[i][j])
			{
				min = this->p->data[i][j];
			}
		}
	}

	return min;
}

template<typename T>
T Mat<T>::Max()
{
	T max = this->p->data[0][0];
	for (int i = 0; i < this->p->height; i++)
	{
		for (int j = 0; j < this->p->width; j++)
		{
			if (this->p->data[i][j] > max)
			{
				max = this->p->data[i][j];
			}
		}
	}

	return max;
}

template<typename T>
T Mat<T>::Max() const
{
	T max = this->p->data[0][0];
	for (int i = 0; i < this->p->height; i++)
	{
		for (int j = 0; j < this->p->width; j++)
		{
			if (this->p->data[i][j] > max)
			{
				max = this->p->data[i][j];
			}
		}
	}

	return max;
}

template<typename T>
T& Mat<T>::At(int row, int col)
{
	while (row < 0)
	{
		row++;
	}

	while (col < 0)
	{
		col++;
	}

	while (row >= this->p->height)
	{
		row--;
	}

	while (col >= this->p->width)
	{
		col--;
	}

	return this->p->data[row][col];
}

template<typename T>
T& Mat<T>::At(int row, int col) const
{
	while (row < 0)
	{
		row++;
	}

	while (col < 0)
	{
		col++;
	}

	while (row >= this->p->height)
	{
		row--;
	}

	while (col >= this->p->width)
	{
		col--;
	}

	return this->p->data[row][col];
}

template<typename T>
void Mat<T>::Set(int row, int col, T value)
{
	this->p->data[row][col] = value;
}

template<typename T>
void Mat<T>::Set(T value)
{
	for (int i = 0; i < this->p->height; i++)
	{
		for (int j = 0; j < this->p->width; j++)
		{
			this->p->data[i][j] = value;
		}
	}
}

template<typename T>
void Mat<T>::Flip(int code)
{
	Proxy<T>* origin = this->p;
	this->p = new Proxy<T>(origin->height, origin->width);

	if (code)
	{
		for (int line = 0; line < this->p->height; line++)
		{
			for (int j = 0; j < this->p->width; j++)
			{
				this->p->data[line][j] = origin->data[this->p->height - 1 - line][j];
			}
		}
	}
	else
	{
		for (int line = 0; line < this->p->width; line++)
		{
			for (int i = 0; i < this->p->height; i++)
			{
				this->p->data[i][line] = origin->data[i][this->p->width - 1 - line];
			}
		}
	}

	if (--origin->referred_count == 0)
		delete origin;
}

template<typename T>
void Mat<T>::Resize(int h, int w)
{
	double i_percent = this->p->height / (double)h;
	double j_percent = this->p->width / (double)w;

	Proxy<T>* origin = this->p;
	this->p = new Proxy<T>(h, w);

	for (int i = 0; i < this->p->height; i++)
	{
		for (int j = 0; j < this->p->width; j++)
		{
			this->p->data[i][j] = origin->data[(int)(i*i_percent)][(int)(j*j_percent)];
		}
	}

	if (--origin->referred_count == 0)
		delete origin;
}

template<typename T>
void Mat<T>::Cut(int x1, int y1, int x2, int y2)
{
	Proxy<T>* origin = this->p;
	this->p = new Proxy<T>(abs(x1 - x2) + 1, abs(y1 - y2) + 1);

	for (int i = 0; i < abs(x1 - x2) + 1; i++)
	{
		for (int j = 0; j < abs(y1 - y2) + 1; j++)
		{
			this->p->data[i][j] = origin->data[x1 + i][y1 + j];
		}
	}

	if (--origin->referred_count == 0)
		delete origin;
}

template<typename T>
void Mat<T>::Rotate(int degree)
{
	while (degree < 0)
		degree += 360;

	degree = degree % 360;

	int num = degree / 90;

	if (num != 1)
	{
		this->Rotate((num - 1) * 90);
	}

	Proxy<T>* origin = this->p;
	this->p = new Proxy<T>(origin->width, origin->height);

	for (int i = 0; i < origin->height; i++)
	{
		for (int j = 0; j < origin->width; j++)
		{
			this->p->data[j][origin->height - 1 - i] = origin->data[i][j];
		}
	}

	if (--origin->referred_count == 0)
		delete origin;
	
}

template<typename T>
void Mat<T>::Transpose()
{
	Proxy<T>* origin = this->p;
	this->p = new Proxy<T>(origin->width, origin->height);

	for (int i = 0; i < this->p->height; i++)
	{
		for (int j = 0; j < this->p->width; j++)
		{
			this->p->data[i][j] = origin->data[j][i];
		}
	}
	
	if (--origin->referred_count == 0)
		delete origin;
}

template<typename T>
void Mat<T>::Reshape(int h, int w)
{
	if (this->p->height * this->p->width != h * w)
	{
		cout << "error" << endl;
		return;
	}

	Proxy<T>* origin = this->p;
	this->p = new Proxy<T>(h, w);

	int i;
	int j;

	for (i = 0; i < origin->height; i++)
		for (j = 0; j < origin->width; j++)
		{
			this->p->data[(origin->width * i + j) / this->p->width][(origin->width * i + j) - ((origin->width * i + j) / this->p->width * this->p->width)] = origin->data[i][j];
		}

	if (--origin->referred_count == 0)
		delete origin;
}

template<typename T>
bool Mat<T>::IsEmpty()
{
	if (this->p->data == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
bool Mat<T>::IsSquare()
{
	if (this->p->height == this->p->width)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
Mat<T>  Mat<T>::MajorDiagonal()
{
	Mat<T> temp(this->p->height, 1);

	for (int n = 0; n < this->p->height; n++)
	{
		temp.p->data[n][0] = this->p->data[n][n];
	}

	return temp;
}

template<typename T>
Mat<T>  Mat<T>::MinorDiagonal()
{
	Mat<T> temp(this->p->height, 1);

	for (int n = 0; n < this->p->height; n++)
	{
		temp.p->data[n][0] = this->p->data[n][this->p->width - 1 - n];
	}

	return temp;
}

template<typename T>
Mat<T> Mat<T>::Row(int n)
{
	Mat<T> temp(1, this->p->width);

	for (int j = 0; j < this->p->width; j++)
	{
		temp.p->data[0][j] = this->p->data[n][j];
	}

	return temp;
}

template<typename T>
Mat<T> Mat<T>::Column(int n)
{
	Mat<T> temp(this->height, 1);

	for (int i = 0; i < this->p->height; i++)
	{
		temp.p->data[i][0] = this->p->data[i][n];
	}

	return temp;
}

template<typename T>
void Mat<T>::Cat(Mat<T> &m, int code)
{
	if (code == 1)
	{
		if (this->p->height != m.p->height)
		{
			cout << "error" << endl;
			return;
		}

		Proxy<T>* origin = this->p;
		this->p = new Proxy<T>(origin->height, origin->width + m.p->width);

		int i;
		int j;

		for (i = 0; i < origin->height; i++)
			for (j = 0; j < origin->width; j++)
			{
				this->p->data[i][j] = origin->data[i][j];
			}

		for (i = 0; i < origin->height; i++)
			for (j = origin->width; j < origin->width + m.p->width; j++)
			{
				this->p->data[i][j] = m.p->data[i][j - origin->width];
			}

		if (--origin->referred_count == 0)
			delete origin;
	}
	
	if (code == 2)
	{
		if (this->p->width != m.p->width)
		{
			cout << "error" << endl;
			return;
		}

		Proxy<T>* origin = this->p;
		this->p = new Proxy<T>(origin->height + m.p->height, origin->width);

		int i;
		int j;


		for (i = 0; i < origin->height; i++)
			for (j = 0; j < origin->width; j++)
			{
				this->p->data[i][j] = origin->data[i][j];
			}

		for (i = origin->height; i < origin->height + m.p->height; i++)
			for (j = 0; j < origin->width; j++)
			{
				this->p->data[i][j] = m.p->data[i - origin->height][j];
			}

		if (--origin->referred_count == 0)
			delete origin;
	}
}

template<typename T>
void Mat<T>::CopyTo(Mat<T> &m)
{
	m.p = this->p;
	++this->p->referred_count;
}

template<typename T>
void Mat<T>::Normalize()
{
	Proxy<T>* origin = this->p;
	this->p = new Proxy<double>(origin->height, origin->width);
	
	double min = origin->data[0][0];
	double max = origin->data[0][0];

	int i;
	int j;

	for (i = 0; i < origin->height; i++)
		for (j = 0; j < origin->width; j++)
		{
			if (origin->data[i][j] > max)
				max = origin->data[i][j];

			if (origin->data[i][j] < min)
				min = origin->data[i][j];
		}

	if (max)
	{
		for (i = 0; i < this->p->height; i++)
			for (j = 0; j < this->p->width; j++)
			{
				this->p->data[i][j] = (origin->data[i][j] - min) / (max - min);
			}
	}

	if (--origin->referred_count == 0)
		delete origin;
}

template<typename T>
Mat<T>& Mat<T>::operator=(const Mat<T> &m)
{
	if (--this->p->referred_count == 0)
		delete this->p;

	this->p = m.p;
	++this->p->referred_count;

	return *this;
}

template<typename T>
bool Mat<T>::operator==(const Mat<T> &m)
{
	if (this->p == m.p)
	{
		return true;
	}
	
	if (this->p->height != m.p->height || this->p->width != m.p->width)
	{
		return false;
	}

	for (int i = 0; i < this->p->height; i++)
	{
		for (int j = 0; j < this->p->width; j++)
		{
			if (this->p->data[i][j] != m.p->data[i][j])
			{
				return false;
			}
		}
	}

	return true;
}

template<typename T>
Mat<T>& Mat<T>::operator++()
{
	for (int i = 0; i < this->p->height; i++)
	{
		for (int j = 0; j < this->p->width; j++)
		{
			++this->p->data[i][j];
		}
	}

	return *this;
}

template<typename T>
Mat<T>& Mat<T>::operator--()
{
	for (int i = 0; i < this->p->height; i++)
	{
		for (int j = 0; j < this->p->width; j++)
		{
			--this->p->data[i][j];
		}
	}

	return *this;
}

template<typename T>
Mat<T> Mat<T>::operator++(int)
{
	Mat<T> temp(*this);

	this->p = new Proxy<T>(temp.p->height, temp.p->width);

	for (int i = 0; i < this->p->height; i++)
	{
		for (int j = 0; j < this->p->width; j++)
		{
			this->p->data[i][j] = temp.p->data[i][j] + 1;
		}
	}

	--temp.p->referred_count;

	return temp;
}

template<typename T>
Mat<T> Mat<T>::operator--(int)
{
	Mat<T> temp(*this);

	this->p = new Proxy<T>(temp.p->height, temp.p->width);

	for (int i = 0; i < this->p->height; i++)
	{
		for (int j = 0; j < this->p->width; j++)
		{
			this->p->data[i][j] = temp.p->data[i][j] - 1;
		}
	}

	--temp.p->referred_count;

	return temp;
}

template<typename T>
Mat<double> Mat<T>::operator-()
{
	Mat<T> temp(*this);

	temp.Normalize();

	temp = 1 - temp;

	return temp;
}

template<typename T>
Mat<T> Mat<T>::gray2bw(T t)
{
	Mat<T> temp(*this);

	temp.Normalize();

	for (int i = 0; i < temp.p->height; i++)
	{
		for (int j = 0; j < temp.p->width; j++)
		{
			if (temp.p->data[i][j] > T)
			{
				temp.p->data[i][j] = 1;
			}
			else
			{
				temp.p->data[i][j] = 0;
			}
		}
	}

	return temp;
}
#endif
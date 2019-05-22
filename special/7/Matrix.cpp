#include "Matrix.h"

#include <iostream>
#include <ctime>

using namespace std;

void Matrix::init(int h, int w)
{
	this->height = h;
	this->width = w;

	this->data = new double*[h];

	for (int i = 0; i < h; i++)
	{
		this->data[i] = new double[w];
	}
}

Matrix::Matrix()
{
	this->height = 0;
	this->width = 0;
	this->data = NULL;
}

Matrix::Matrix(int h, int w)
{
	this->init(h, w);
}

Matrix::Matrix(int h, int w, double val)
{
	this->init(h, w);

	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			this->data[i][j] = val;
		}
}
Matrix::Matrix(const Matrix &m)
{
	this->init(m.height, m.width);

	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
		{
			this->data[i][j] = m.data[i][j];
		}
}

Matrix::~Matrix()
{

	if (this->data)
	{
		for (int i = 0; i < this->height; i++)
		{
			delete[] this->data[i];
		}
		delete[] this->data;
	}

}

void Matrix::Zeros(int h, int w) // ���ݲ�������h��w�е�ȫ�����
{
	this->init(h, w);

	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
		{
			this->data[i][j] = 0;
		}
}

void Matrix::Ones(int h, int w) // ���ݲ�������h��w�е�ȫ1����
{
	this->init(h, w);

	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
		{
			this->data[i][j] = 1;
		}
}

void Matrix::Random(int h, int w) //����h��w�е�������󣬾����Ԫ��Ϊ[0,1]֮������ʵ����double���ͣ�
{
	srand(time(0));

	this->init(h, w);

	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
		{
			this->data[i][j] = rand() / double(RAND_MAX);
		}
}

void Matrix::Identity(int n) // ���ݲ�������n��n�еĵ�λ����
{
	this->init(n, n);

	for (int i = 0; i < this->height; i++)
	{
		this->data[i][i] = 1;
	}
}

int Matrix::Height()  // ��þ��������
{
	return this->height;
}

int Matrix::Width()   // ��þ��������
{
	return this->width;
}

Matrix Matrix::MajorDiagonal()// ��������Խ����ϵ�Ԫ�أ����һ��N��1�еľ���NΪ���Խ���Ԫ�صĸ���
{
	Matrix temp(this->width, 1);

	for (int n = 0; n < this->width; n++)
	{
		temp.data[n][0] = this->data[n][n];
	}

	return temp;
}

Matrix Matrix::MinorDiagonal()// �����ĸ��Խ����ϵ�Ԫ�أ����һ��N��1�еľ���NΪ���Խ�����Ԫ�صĸ���
{
	Matrix temp(this->width, 1);

	for (int n = 0; n < this->width; n++)
	{
		temp.data[n][0] = this->data[this->height - 1 - n][n];
	}

	return temp;
}

Matrix Matrix::Row(int n)// ���ؾ���ĵ�n���ϵ�Ԫ�أ����һ��1��N�еľ��������NΪ��n����Ԫ�صĸ���
{
	Matrix temp(1, this->width);

	for (int m = 0; m < this->width; m++)
	{
		temp.data[0][m] = this->data[n][m];
	}

	return temp;
}

Matrix Matrix::Column(int n)// ���ؾ���ĵ�n���ϵ�Ԫ�أ����һ��N��1�еľ��������NΪ��n����Ԫ�صĸ���
{
	Matrix temp(this->height, 1);

	for (int m = 0; m < this->height; m++)
	{
		temp.data[m][0] = this->data[m][n];
	}

	return temp;
}

void Matrix::Transpose() // ������ת��
{
	double** origin = this->data;
	int i;
	int j;

	this->init(this->width, this->height);

	for (i = 0; i < this->height; i++)
		for (j = 0; j < this->width; j++)
		{
			this->data[i][j] = origin[j][i];
		}

	for (i = 0; i < this->width; i++)
		delete[] origin[i];
	delete[] origin;
}

double& Matrix::At(int row, int col) //��ȡ��row�е�col�еľ���Ԫ�ص�ֵ
{
	return this->data[row][col];
}

void Matrix::Set(int row, int col, double value) //���õ�row�е�col�о���Ԫ�ص�ֵΪvalue
{
	this->data[row][col] = value;
}

void Matrix::Set(double value) //���þ�������Ԫ��Ϊͬһֵvalue
{
	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
		{
			this->data[i][j] = value;
		}
}

void Matrix::Normalize() // �ú����Ѿ������������������[0,1]���䣬���ѵ�ǰ��������Ԫ���е���Сֵmin���0�����ֵmax��Ϊ1������Ԫ�ص�ֵ���Ա䵽[0,1]���䣬��ʽΪ��t��=(t-min)/max;
{
	double min = this->data[0][0];
	double max = this->data[0][0];
	int i;
	int j;

	for (i = 0; i < this->height; i++)
		for (j = 0; j < this->width; j++)
		{
			if (this->data[i][j] > max)
				max = this->data[i][j];

			if (this->data[i][j] < min)
				min = this->data[i][j];
		}

	if (max)
	{
		for (i = 0; i < this->height; i++)
			for (j = 0; j < this->width; j++)
			{
				this->data[i][j] = (this->data[i][j] - min) / max;
			}
	}
}

void Matrix::Reshape(int h, int w) //�ھ���Ԫ���������������£����������б�Ϊ���������Ĵ�С
{
	if (this->height * this->width != h * w)
	{
		cout << "error" << endl;
		return;
	}

	double** origin = this->data;
	int origin_h = this->height;
	int origin_w = this->width;

	int i;
	int j;

	this->init(h, w);

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

bool Matrix::IsEmpty()// �жϾ����Ƿ�Ϊ�վ���
{
	if (this->data)
		return false;
	else
		return true;
}

bool Matrix::IsSquare()// �жϾ����Ƿ�Ϊ����
{
	if (this->height == this->width)
		return true;
	else
		return false;
}

void Matrix::CopyTo(Matrix &m) // �������Ƹ�m
{
	int i;
	int j;

	for (i = 0; i < m.height; i++)
		delete[] m.data[i];
	delete[] m.data;

	m.init(this->height, this->width);

	for (i = 0; i < this->height; i++)
		for (j = 0; j < this->width; j++)
		{
			m.data[i][j] = this->data[i][j];
		}
}

void Matrix::Mul(double s) // �����ÿ��Ԫ�ض����Բ���s
{
	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
		{
			this->data[i][j] *= s;
		}
}

void Matrix::Cat(Matrix &m, int code) // ������m�뵱ǰ�������ƴ�ӣ�code����ƴ�ӵķ�ʽ����mƴ�ӵ���ǰ������ϡ��¡����ң��������Ӽ�����ٺ����˵��
{
	if (code == 1)
	{
		if (this->height != m.height)
		{
			cout << "error" << endl;
			return;
		}

		double** origin = this->data;
		int origin_h = this->height;
		int origin_w = this->width;

		int i;
		int j;

		this->init(this->height, this->width + m.width);

		for (i = 0; i < origin_h; i++)
			for (j = 0; j < origin_w; j++)
			{
				this->data[i][j] = origin[i][j];
			}

		for (i = 0; i < origin_h; i++)
			for (j = origin_w; j < origin_w + m.width; j++)
			{
				this->data[i][j] = m.data[i][j - origin_w];
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

		double** origin = this->data;
		int origin_h = this->height;
		int origin_w = this->width;

		int i;
		int j;

		this->init(this->height + m.height, this->width);

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

Matrix Add(const Matrix &m1, const Matrix &m2) // ��Ԫ������������m1��m2��ӣ����������Ϊ�����ķ���ֵ
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

Matrix Sub(const Matrix &m1, const Matrix &m2) // ��Ԫ������������m1��m2��������������Ϊ�����ķ���ֵ
{

	if (m1.height != m2.height || m1.width != m2.width)
	{
		Matrix m;
		cout << "error" << endl;
		return m;
	}
	
	/*Matrix m(m1.height, m1.width);
	
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
	
	return m;*/
	Matrix m(m1 - m2);
	return m;
}

void Swap(Matrix &a, Matrix &b) // ��Ԫ������������������
{
	if (a.height != b.height || a.width != b.width)
	{
		cout << "error" << endl;
		return;
	}

	for (int i = 0; i < a.height; i++)
		for (int j = 0; j < a.width; j++)
		{
			int temp = a.data[i][j];
			a.data[i][j] = b.data[i][j];
			b.data[i][j] = temp;
		}
}

//��������غ�����
Matrix& Matrix::operator=(const Matrix &m)  //���ظ�ֵ���������ɶ����Ŀ�����
{
	int i;
	int j;

	if (this->data)
	{
		for (i = 0; i < this->height; i++)
		{
			delete[] this->data[i];
		}
		delete[] this->data;
	}

	this->init(m.height, m.width);

	for (i = 0; i < this->height; i++)
		for (j = 0; j < this->width; j++)
		{
			this->data[i][j] = m.data[i][j];
		}

	return *this;
}

Matrix& Matrix::operator=(double num)
{
	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
		{
			this->data[i][j] = num;
		}

	return *this;
}

bool Matrix::operator==(const Matrix &m)  //�ж�����Matrix�����Ƿ����
{
	if (this->height != m.height || this->width != m.width)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < this->height; i++)
			for (int j = 0; j < this->width; j++)
			{
				if (this->data[i][j] != m.data[i][j])
				{
					return false;
				}
			}

		return true;
	}

}
Matrix Matrix::operator+(const Matrix &m)  //�����ߴ���ͬ�ľ��󣬶�ӦԪ�ص���ֵ��ӣ�
{
	if (this->height == m.height && this->width == m.width)
	{
		Matrix m(this->height, this->width);
		for (int i = 0; i < this->height; i++)
			for (int j = 0; j < this->width; j++)
			{
				m.data[i][j] = this->data[i][j] + m.data[i][j];
			}

		return m;
	}
	else
	{
		Matrix m;
		return m;
	}
}

Matrix Matrix::operator-(const Matrix &m) const  //�����ߴ���ͬ�ľ��󣬶�ӦԪ�ص���ֵ�����
{
	if (this->height == m.height && this->width == m.width)
	{
		Matrix result(this->height, this->width);
		for (int i = 0; i < this->height; i++)
			for (int j = 0; j < this->width; j++)
			{
				result.data[i][j] = this->data[i][j] - m.data[i][j];
			}

		return result;
	}
	else
	{
		Matrix result;
		return result;
	}
}



Matrix& Matrix::operator++()  //ǰ���Լӣ�
{
	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
		{
			this->data[i][j]++;
		}

	return *this;
}

Matrix& Matrix::operator--()  //ǰ���Լ���
{
	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
		{
			this->data[i][j]--;
		}

	return *this;
}

Matrix Matrix::operator++(int)  //�����Լӣ�
{
	Matrix origin(*this);

	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			this->data[i][j]++;
		}
	}

	return origin;
}

Matrix Matrix::operator--(int)  //�����Լ���
{
	Matrix origin(*this);

	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			this->data[i][j]--;
		}
	}

	return origin;
}

//����Ԫ�ؼ���ͬһ��ֵ;
Matrix operator+(Matrix &m, double num)
{
	Matrix result(m);
	for (int i = 0; i < result.height; i++)
		for (int j = 0; j < result.width; j++)
		{
			result.data[i][j] += num;
		}

	return result;
}

//����Ԫ�ؼ�ȥͬһ��ֵ;
Matrix operator-(Matrix &m, double num)
{
	return m + (-num);
}

//����Ԫ�س���ͬһ��ֵ;
Matrix operator*(Matrix &m, double num)
{
	Matrix result(m);

	for (int i = 0; i < m.height; i++)
		for (int j = 0; j < m.width; j++)
		{
			m.data[i][j] *= num;
		}

	return result;
}

//����Ԫ�س���ͬһ��ֵ;
Matrix operator/(Matrix &m, double num)
{
	return m * (1 / num);
}
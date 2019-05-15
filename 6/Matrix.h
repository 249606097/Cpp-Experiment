#ifndef Matrix_H
#define Matrix_H

class Matrix
{
    public:
        Matrix();
        Matrix(int h,int w);
        Matrix(int h, int w, double val);
        Matrix(const Matrix &m);
        virtual ~Matrix();

        void Zeros(int h, int w); // 根据参数产生h行w列的全零矩阵
        void Ones(int h, int w); // 根据参数产生h行w列的全1矩阵
        void Random(int h, int w); //产生h行w列的随机矩阵，矩阵的元素为[0,1]之间的随机实数（double类型）
        void Identity(int n); // 根据参数产生n行n列的单位矩阵

        int Height();  // 获得矩阵的行数
        int Width();   // 获得矩阵的列数
        Matrix MajorDiagonal();// 求矩阵主对角线上的元素，输出一个N行1列的矩阵，N为主对角线元素的个数
        Matrix MinorDiagonal();// 求矩阵的副对角线上的元素，输出一个N行1列的矩阵，N为副对角线上元素的个数
        Matrix Row(int n);// 返回矩阵的第n行上的元素，组出一个1行N列的矩阵输出，N为第n行上元素的个数
        Matrix Column(int n);// 返回矩阵的第n列上的元素，组出一个N行1列的矩阵输出，N为第n列上元素的个数
        
        void Transpose(); // 将矩阵转置

        double& At(int row, int col); //获取第row行第col列的矩阵元素的值
        void Set(int row, int col, double value); //设置第row行第col列矩阵元素的值为value
        void Set(double value); //设置矩阵所有元素为同一值value

        void Normalize(); // 该函数把矩阵的数据线性缩放至[0,1]区间，即把当前矩阵所有元素中的最小值min变成0，最大值max变为1，其他元素的值线性变到[0,1]区间，公式为：t’=(t-min)/max;

        virtual void Reshape(int h, int w); //在矩阵元素总数不变的情况下，将矩阵行列变为参数给定的大小
        bool IsEmpty();// 判断矩阵是否为空矩阵
        bool IsSquare();// 判断矩阵是否为方阵
        void CopyTo(Matrix &m); // 将矩阵复制给m
        void Mul(double s); // 矩阵的每个元素都乘以参数s
        void Cat(Matrix &m, int code); // 将矩阵m与当前矩阵进行拼接，code代表拼接的方式：将m拼接到当前矩阵的上、下、左、右，具体例子见本大纲后面的说明

        friend Matrix Add(const Matrix &m1, const Matrix &m2); // 友元函数，将矩阵m1和m2相加，结果矩阵作为函数的返回值
        friend Matrix Sub(const Matrix &m1, const Matrix &m2); // 友元函数，将矩阵m1和m2相减，结果矩阵作为函数的返回值
        friend void Swap(Matrix &a, Matrix &b); // 友元函数，交换两个矩阵

        void init(int h, int w);
        int height;
        int width;
		double **data;
};

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

void Matrix::Zeros(int h, int w) // 根据参数产生h行w列的全零矩阵
{
	this->init(h, w);

	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
		{
			this->data[i][j] = 0;
		}
}

void Matrix::Ones(int h, int w) // 根据参数产生h行w列的全1矩阵
{
	this->init(h, w);

	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
		{
			this->data[i][j] = 1;
		}
}

void Matrix::Random(int h, int w) //产生h行w列的随机矩阵，矩阵的元素为[0,1]之间的随机实数（double类型）
{
	srand(time(0));

	this->init(h, w);

	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
		{
			this->data[i][j] = rand() / double(RAND_MAX);
		}
}

void Matrix::Identity(int n) // 根据参数产生n行n列的单位矩阵
{
	this->init(n, n);

	for (int i = 0; i < this->height; i++)
	{
		this->data[i][i] = 1;
	}
}

int Matrix::Height()  // 获得矩阵的行数
{
	return this->height;
}

int Matrix::Width()   // 获得矩阵的列数
{
	return this->width;
}

Matrix Matrix::MajorDiagonal()// 求矩阵主对角线上的元素，输出一个N行1列的矩阵，N为主对角线元素的个数
{
	Matrix temp(this->width, 1);

	for (int n = 0; n < this->width; n++)
	{
		temp.data[n][0] = this->data[n][n];
	}

	return temp;
}

Matrix Matrix::MinorDiagonal()// 求矩阵的副对角线上的元素，输出一个N行1列的矩阵，N为副对角线上元素的个数
{
	Matrix temp(this->width, 1);

	for (int n = 0; n < this->width; n++)
	{
		temp.data[n][0] = this->data[this->height - 1 - n][n];
	}

	return temp;
}

Matrix Matrix::Row(int n)// 返回矩阵的第n行上的元素，组出一个1行N列的矩阵输出，N为第n行上元素的个数
{
	Matrix temp(1, this->width);

	for (int m = 0; m < this->width; m++)
	{
		temp.data[0][m] = this->data[n][m];
	}

	return temp;
}

Matrix Matrix::Column(int n)// 返回矩阵的第n列上的元素，组出一个N行1列的矩阵输出，N为第n列上元素的个数
{
	Matrix temp(this->height, 1);

	for (int m = 0; m < this->height; m++)
	{
		temp.data[m][0] = this->data[m][n];
	}

	return temp;
}

void Matrix::Transpose() // 将矩阵转置
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

double& Matrix::At(int row, int col) //获取第row行第col列的矩阵元素的值
{
	return this->data[row][col];
}

void Matrix::Set(int row, int col, double value) //设置第row行第col列矩阵元素的值为value
{
	this->data[row][col] = value;
}

void Matrix::Set(double value) //设置矩阵所有元素为同一值value
{
	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
		{
			this->data[i][j] = value;
		}
}

void Matrix::Normalize() // 该函数把矩阵的数据线性缩放至[0,1]区间，即把当前矩阵所有元素中的最小值min变成0，最大值max变为1，其他元素的值线性变到[0,1]区间，公式为：t’=(t-min)/max;
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

void Matrix::Reshape(int h, int w) //在矩阵元素总数不变的情况下，将矩阵行列变为参数给定的大小
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

bool Matrix::IsEmpty()// 判断矩阵是否为空矩阵
{
	if (this->data)
		return false;
	else
		return true;
}

bool Matrix::IsSquare()// 判断矩阵是否为方阵
{
	if (this->height == this->width)
		return true;
	else
		return false;
}

void Matrix::CopyTo(Matrix &m) // 将矩阵复制给m
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

void Matrix::Mul(double s) // 矩阵的每个元素都乘以参数s
{
	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
		{
			this->data[i][j] *= s;
		}
}

void Matrix::Cat(Matrix &m, int code) // 将矩阵m与当前矩阵进行拼接，code代表拼接的方式：将m拼接到当前矩阵的上、下、左、右，具体例子见本大纲后面的说明
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
			for (j = origin_w; i < origin_w + m.width; j++)
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

Matrix Add(const Matrix &m1, const Matrix &m2) // 友元函数，将矩阵m1和m2相加，结果矩阵作为函数的返回值
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

Matrix Sub(const Matrix &m1, const Matrix &m2) // 友元函数，将矩阵m1和m2相减，结果矩阵作为函数的返回值
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

void Swap(Matrix &a, Matrix &b) // 友元函数，交换两个矩阵
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

#endif

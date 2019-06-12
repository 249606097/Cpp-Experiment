#ifndef FILTER_H
#define FILTER_H

#include "Image.h"

class Filter
{
public:
	Filter(int size); //构造函数
	virtual ~Filter(); //析构函数;

	virtual Matrix Filtering(const Matrix &input) = 0;  //滤波函数（纯虚函数）;

protected:
	int filterSize;
};

#endif

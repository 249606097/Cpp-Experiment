#ifndef FIL_HPP
#define FIL_HPP

#include "Mat.hpp"
#include <algorithm>

template <class T>
class Filter
{
public:
	Filter(int size); //构造函数
	virtual ~Filter(); //析构函数;
	virtual Mat<T> Filtering(const Mat<T> &input) = 0; //滤波函数（纯虚函数）;
protected:
	int filterSize;
};

//meanFilter类
template <class T>
class MeanFilter : public Filter<T>
{
public:
	MeanFilter(int size);
	virtual ~MeanFilter();
	virtual Mat<T> Filtering(const Mat<T> &input); //均值滤波函数
};


//median类
template <class T>
class MedianFilter : public Filter<T>
{
public:
	MedianFilter(int size);
	virtual ~MedianFilter();
	virtual Mat<T> Filtering(const Mat<T> &input); // 中值滤波器函数
};

template<typename T>
Filter<T>::Filter(int size)
{
	this->filterSize = size;
}

template<typename T>
Filter<T>::~Filter()
{

}

template<typename T>
MeanFilter<T>::MeanFilter(int size) : Filter(size)
{

}

template<typename T>
MeanFilter<T>::~MeanFilter()
{

}

template<typename T>
Mat<T> MeanFilter<T>::Filtering(const Mat<T> &input)
{
	int height = input.Height();
	int width = input.Width();

	Mat<T> m(height, width);

	T mean = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			for (int area_x = i - (this->filterSize - 1) / 2; area_x - i < (this->filterSize - 1) / 2 + 1; area_x++)
			{
				for (int area_y = j - (this->filterSize - 1) / 2; area_y - j < (this->filterSize - 1) / 2 + 1; area_y++)
				{
					mean += input.At(area_x, area_y);
				}
			}

			mean /= this->filterSize * this->filterSize;
			m.Set(i, j, mean);
		}
	}

	return m;
}


template<typename T>
MedianFilter<T>::MedianFilter(int size) : Filter(size)
{

}

template<typename T>
MedianFilter<T>::~MedianFilter()
{

}

template<typename T>
Mat<T> MedianFilter<T>::Filtering(const Mat<T> &input)
{
	int height = input.Height();
	int width = input.Width();

	Mat<T> m(height, width);

	T* data = new T[this->filterSize*this->filterSize];

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{

			int place = 0;
			for (int area_x = i - (this->filterSize - 1) / 2; area_x - i < (this->filterSize - 1) / 2 + 1; area_x++)
			{
				for (int area_y = j - (this->filterSize - 1) / 2; area_y - j < (this->filterSize - 1) / 2 + 1; area_y++)
				{
					data[place] = input.At(area_x, area_y);
					place++;
				}
			}

			std::sort(data, data + this->filterSize*this->filterSize);

			m.Set(i, j, data[this->filterSize*this->filterSize / 2]);
		}
	}

	delete[] data;

	return m;
}
#endif
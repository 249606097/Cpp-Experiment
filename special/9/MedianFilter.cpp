#include "MedianFilter.h"
#include <algorithm>

MedianFilter::MedianFilter(int size) : Filter(size)
{

}

MedianFilter::~MedianFilter()
{

}

Matrix MedianFilter::Filtering(const Matrix &input)
{
	int height = input.Height();
	int width = input.Width();

	Matrix m(height, width);
	
	double* data = new double[this->filterSize*this->filterSize];

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
#include "MeanFilter.h"

MeanFilter::MeanFilter(int size) : Filter(size)
{

}

MeanFilter::~MeanFilter()
{

}

Matrix MeanFilter::Filtering(const Matrix &input)
{
	int height = input.Height();
	int width = input.Width();

	Matrix m(height, width);

	double mean = 0;
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
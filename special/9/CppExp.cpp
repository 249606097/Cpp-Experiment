#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "highgui.h"
#include "Filter.hpp"
#include "Mat.hpp"

int main(int argc, char* argv[])
{
	Mat<double> m("Fruits.jpg");
	m.Show("origin");

	m.Normalize();

	m = (-m) * 255;
	m.Show("normalize");

	cout << m.At(200, 200) << endl;

	m.Rotate(270);
	m.Show("rotate");

	m.Resize(600, 600);
	m.Show("resize");

	m.Cut(100, 100, 400, 400);
	m.Show("cut");

	Mat<double> temp(m);

	m.Cat(temp, 1);
	m.Show("cat");
	
	m = m + 50;
	m.Show("+50");

	m = m - 100;
	m.Show("-50");

	Mat<double> mf("Lena_gaussian.jpg");

	mf.Show("Origin");

	Filter<double> *filter = NULL;
	filter = new MeanFilter<double>(5);
	Mat<double> result_mean;
	result_mean = filter->Filtering(mf);
	result_mean.Show("Mean");
	delete filter;


	filter = new MedianFilter<double>(5);
	Mat<double> result_median;
	result_median = filter->Filtering(mf);
	result_median.Show("Median");
	delete filter;

	Mat<double> result_sub(mf - result_mean);
	result_sub.Show("filter_sub");

	return 0;
}

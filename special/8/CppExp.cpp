#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "highgui.h"
#include "Image.h"
#include "MeanFilter.h"
#include "MedianFilter.h"


int main(int argc, char* argv[])
{
	Image img("Lena_gaussian.jpg");
	img.Show("Origin");

	Filter *filter = NULL;
	filter = new MeanFilter(5);
	Image result_mean;
	result_mean = filter->Filtering(img);
	result_mean.Show("Mean");
	delete filter;

	filter = new MedianFilter(5);
	Image result_median;
	result_median = filter->Filtering(img);
	result_median.Show("Median");
	delete filter;


	return 0;
}

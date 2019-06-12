#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H

#include "Filter.h"

class MedianFilter : public Filter
{
public:
	MedianFilter(int size);
	virtual ~MedianFilter();
	virtual Matrix Filtering(const Matrix &input);  // ÖÐÖµÂË²¨Æ÷º¯Êý
};

#endif

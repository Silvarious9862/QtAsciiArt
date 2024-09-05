#include "MatrixIterator.h"
#include <vector>

MatrixIterator& MatrixIterator::operator++(int)
{
	beginX += step;
	if (beginX > ptr_col.size()) {
		beginX = 0;
		beginY += step;
		rowDone = true;
	}
	if (beginY > ptr_row->size()) {
		beginX = NULL;
		beginY = NULL;
		fullDone = true;
	}
	return *this;
}

double MatrixIterator::CountAvg()
{
    if (step == -4) step = 15;
	double avg = 0;
	int count = 0;
	for (currentY = beginY; (currentY < beginY + step) && (currentY < ptr_row->size()); currentY++) {	// for rows
		for (currentX = beginX; (currentX < beginX + step) && (currentX < ptr_col.size()); currentX++) {// for elems
			avg += matrix->at(currentY).at(currentX);	// sum of pixels
			count++;
		}
	}
	return avg / count;
}

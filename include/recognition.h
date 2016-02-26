#ifndef RECOGNITION_H
#define RECOGNITION_H

#include<opencv/cv.h>
#include<opencv/highgui.h>
#include<opencv/cvaux.h>
#include<iostream>
#include<fstream>
#include "include.h"

#define GENERATE_DATASET false
#define MAX_HISTOGRAMS 5
//#define DIFFERENT 0.24
//#define EXTREME 0.15
#define EXTREME 0.24
#define DIFFERENT 0.42

class personHistogram
{
	public:
	CvHistogram* A[MAX_HISTOGRAMS];
	CvHistogram* B[MAX_HISTOGRAMS];
	int currHistograms;
	int noOfMatches[MAX_HISTOGRAMS];
	
	personHistogram();
};

int findMinIndex(int *p, int len);
int findMaxCompare(personHistogram *p, CvHistogram *histA, CvHistogram *histB, int len);
int recognition(IplImage *inc_image, int cameraIndex);

#endif

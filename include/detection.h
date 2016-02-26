#ifndef DETECTION_H
#define DETECTION_H

#include<opencv/cv.h>
#include<opencv/highgui.h>
#include<opencv/cvaux.h>
#include<iostream>
#include<vector>
#include<cstring>
#include "include.h"

void transform(int x, int y, float *px, float *py, double *i);
void drawHori(int u1, int l1, int u2, int l2, double *i, IplImage *img);
void drawVert(int u1, int l1, int u2, int l2, double *i, IplImage *img);
void detectBodies(IplImage *img, char* windowName, int cameraIndex);

#endif

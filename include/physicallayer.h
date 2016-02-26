#ifndef PHYSICALLAYER_H
#define PHYSICALLAYER_H

#include<fstream>
#include<vector>
#include<iomanip>
#include<cstring>
#include<cmath>
#include<limits>
#include "include.h"

#define MAX_PAST_RECORDS 40
#define AVERAGING_FRAMES 5
#define MAX_LATENCY 50
#define PHYSICAL_LAYER_TR 5
#define EPSI 0.95

#define sg(y) (((y) > 0) ? '+' : '-')

int findROI(int pi,float x, float y, float vx, float vy,  int cameraIndex);
int findROIindex(float x, float y, int cameraIndex);
void personUpdate(vector<int> peopleRecognised, vector<float> worldXs, vector<float> worldYs, int cameraIndex, int frameNumber);

#endif

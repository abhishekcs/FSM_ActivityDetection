#ifndef SETROI_H
#define SETROI_H

#include<opencv/cv.h>
#include<opencv/highgui.h>
#include<opencv/cvaux.h>
#include<opencv/cxcore.h>
#include<iostream>
#include<fstream>
#include "include.h"

void on_mouseROI(int event, int x, int y, int flags, void *params);
void setROI(int argc, char **argv);

#endif

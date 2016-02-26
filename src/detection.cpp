#include "../include/detection.h"
#include "../include/recognition.h"
#include "../include/physicallayer.h"

extern CvHaarClassifierCascade *cascade;
extern CvMemStorage *storage;
extern CvFont font;
extern double homography[NO_OF_CAMERAS][9];
extern double invHomography[NO_OF_CAMERAS][9];
extern int frameCount[NO_OF_CAMERAS];

void transform(int x, int y, float *px, float *py, double *i)
{
    float Z = 1.0/(i[6]*x+i[7]*y+i[8]);
    *px = ((i[0]*x+i[1]*y+i[2])*Z);
    *py = ((i[3]*x+i[4]*y+i[5])*Z);
}

void drawHori(int lowerX, int upperX, int lowerY, int upperY, double *i, IplImage *img)
{
    float x1, x2, y1, y2;
    for (int j = lowerY; j <= upperY; j += 4)
    {
        transform(lowerX, j, &x1, &y1, i);
        transform(upperX, j, &x2, &y2, i);
    	cvLine(img, cvPoint(x1, y1), cvPoint(x2, y2), CV_RGB(0, 0, 255), 1, 8, 0);
    }
}

void drawVert(int lowerX, int upperX, int lowerY, int upperY, double *i, IplImage *img)
{
    float x1, x2, y1, y2;
    for (int j = lowerX; j <= upperX; j += 4)
    {
        transform(j, lowerY, &x1, &y1, i);
        transform(j, upperY, &x2, &y2, i);
        cvLine(img, cvPoint(x1, y1), cvPoint(x2, y2), CV_RGB(0, 0, 255), 1, 8, 0);
    }
}

void detectBodies(IplImage *img, char* windowName, int cameraIndex)
{
	ASSERT(img);
	frameCount[cameraIndex]++;
	PRINTVAL(cameraIndex);
	PRINTVAL(frameCount[cameraIndex]);
	IplImage* imgToBeShown = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	cvCopy(img, imgToBeShown);
	int t = cvGetTickCount();
	//CvSeq *bodies = cvHaarDetectObjects(img, cascade, storage, 1.02, 30, 0, cvSize(120, 200));
	//CvSeq *bodies = cvHaarDetectObjects(img, cascade, storage, 1.01, 10, 0, cvSize(120, 200));
	CvSeq *bodies = cvHaarDetectObjects(img, cascade, storage, 1.01, 20, 0, cvSize(120, 200));
	vector<int> peopleRecognised;
	vector<float> worldXs;
	vector<float> worldYs;
	for (int i = 0; i < (bodies ? bodies->total : 0); i++)
    {
       	CvRect* r = (CvRect*)cvGetSeqElem(bodies, i);
       	int midX = round(r->x+r->width/2.0);
       	int midY = round(r->y+r->height/2.0);
       	int newWidth = round(r->width*0.4);
       	int newHeight = round(newWidth*4.0);
    	cvSetImageROI(img, cvRect(round(midX-newWidth/2.0), round(midY-newHeight/2.0), newWidth, newHeight));
        IplImage *imgtemp = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
        cvCopy(img, imgtemp, NULL);
        PRINT("PRE-RECOGNITION");
        int perIndex = recognition(imgtemp, cameraIndex);
        PRINT("POST-RECOGNITION");
        cvResetImageROI(img);
        cvRectangle(imgToBeShown, cvPoint(round(midX-newWidth/2.0), round(midY-newHeight/2.0)), cvPoint(round(midX+newWidth/2.0), round(midY+newHeight/2.0)), CV_RGB(0, 255, 0), 3, 8, 0);
        char identity[3];
        sprintf(identity, "%d", perIndex+1);
        cvPutText(imgToBeShown, identity, cvPoint(r->x, r->y), &font, cvScalar(0, 0, 255));
        peopleRecognised.push_back(perIndex);
        float worldX, worldY;
        PRINTVAL(midX);
        PRINTVAL(round(midY+newHeight/2.0));
        transform(midX, round(midY+newHeight/2.0), &worldX, &worldY, homography[i]);
        PRINTVAL(worldX);
        PRINTVAL(worldY);
        worldXs.push_back(worldX);
        worldYs.push_back(worldY);
    }
	personUpdate(peopleRecognised, worldXs, worldYs, cameraIndex, frameCount[cameraIndex]);         
    t = cvGetTickCount() - t;
    cout << "detection time = " << t/(cvGetTickFrequency()*1000) << " ms\n";
    switch(cameraIndex)
    {
    	case 0:
	   		drawHori(0,8,0,30,invHomography[cameraIndex],imgToBeShown);
    		drawVert(0,8,0,30,invHomography[cameraIndex],imgToBeShown);
    		break;
    	case 1:
	   		drawHori(0,8,110,160,invHomography[cameraIndex],imgToBeShown);
    		drawVert(0,8,110,160,invHomography[cameraIndex],imgToBeShown);
    		break;
    	case 2:
	   		drawHori(0,8,40,90,invHomography[cameraIndex],imgToBeShown);
    		drawVert(0,8,40,90,invHomography[cameraIndex],imgToBeShown);
    		break;
    	case 3:
	   		drawHori(0,8,70,110,invHomography[cameraIndex],imgToBeShown);
    		drawVert(0,8,70,110,invHomography[cameraIndex],imgToBeShown);
    		break;
    	default:
    		break;
    }
    cvShowImage(windowName, imgToBeShown);
	cvReleaseImage(&imgToBeShown);
}

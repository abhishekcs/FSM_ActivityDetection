#include "../include/setROI.h"

int noOfROI;
ofstream wrROI;

void on_mouseROI(int event, int x, int y, int flags, void *params)
{
	if (noOfROI == 0)
		return;
	IplImage *img = (IplImage*)params;
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		cvRectangle(img, cvPoint(x-2, y-2), cvPoint(x+2, y+2), cvScalar(0, 0, 255), 5, 8, 0);
		cvShowImage("SETROI", img);
		cout << "Enter ROI name: ";
		char ROIName[20];
		cin >> ROIName;
		wrROI << x << "\t" << y << "\t" << ROIName << "\n";
		noOfROI--;
	}
	else
	{
		IplImage *temp = cvCreateImage(cvSize(img->width, img->height), img->depth, img->nChannels);
		cvCopy(img, temp);  
		cvCircle(temp, cvPoint(x, y), 1, cvScalar(255, 0, 0), 5, 8, 0);
		cvShowImage("SETROI", temp);
		cvReleaseImage(&temp);
	}
	cvWaitKey(0);
}

void setROI(int argc, char **argv)
{
	bool cameraFeed = false;
	if (argc == 0)
		cameraFeed = true;
	else
	{
		if (argc < NO_OF_CAMERAS)
		{
			cout << "Please provide " << NO_OF_CAMERAS << " video files\n";
			exit(1);
		}		
	}
	CvCapture *capture[NO_OF_CAMERAS];
	IplImage* images[NO_OF_CAMERAS];
	for (int i = 0; i < NO_OF_CAMERAS; i++)
	{
		if (cameraFeed == true)
			capture[i] = cvCaptureFromCAM(i);
		else
			capture[i] = cvCaptureFromFile(argv[i]);
		images[i] = cvQueryFrame(capture[i]);
	}
	ASSERT(images[0] != NULL);
	char ROIpath[60];
	strcpy(ROIpath, PROJECT_PATH);
	strcat(ROIpath, "files/ROI");
	wrROI.open(ROIpath);
	wrROI << NO_OF_CAMERAS << endl;
	cvNamedWindow("SETROI");
	int i = 0;
	while (i < NO_OF_CAMERAS)
	{
		cout << "Enter the number of ROIs to be marked: ";
		cin >> noOfROI;
		wrROI << noOfROI << "\n";
		cvShowImage("SETROI", images[i]);
		cvSetMouseCallback("SETROI", on_mouseROI, (void*)images[i]);
		cvWaitKey(0);
		i++;
	}
	for (int i = 0; i < NO_OF_CAMERAS; i++)
		cvReleaseCapture(&capture[i]);
	wrROI.close();
	cvDestroyWindow("SETROI");
}

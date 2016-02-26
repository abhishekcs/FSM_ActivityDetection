#include "../include/setHomography.h"

int noOfPoints;
ofstream wrHomography;

void on_mouseHomography(int event, int x, int y, int flags, void *params)
{
	if (noOfPoints == 0)
		return;
	IplImage *img = (IplImage*)params;
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		cvRectangle(img, cvPoint(x-2, y-2), cvPoint(x+2, y+2), cvScalar(0, 0, 255), 5, 8, 0);
		cvShowImage("SETHOMOGRAPHY", img);
		float worldX, worldY;
		cout << "Enter World X: ";
		cin >> worldX;
		cout << "Enter World Y: ";
		cin >> worldY;
		wrHomography << x << "\t" << y << "\t" << worldX << "\t" << worldY << "\n";
		noOfPoints--;
	}
	else
	{
		IplImage *temp = cvCreateImage(cvSize(img->width, img->height), img->depth, img->nChannels);
		cvCopy(img, temp);  
		cvCircle(temp, cvPoint(x, y), 1, cvScalar(255, 0, 0), 5, 8, 0);
		cvShowImage("SETHOMOGRAPHY", temp);
		cvReleaseImage(&temp);
	}
	cvWaitKey(0);
}

void setHomography(int argc, char **argv)
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
	char homographypath[60];
	strcpy(homographypath, PROJECT_PATH);
	strcat(homographypath, "files/homography");
	wrHomography.open(homographypath);
	wrHomography << NO_OF_CAMERAS << endl;
	cvNamedWindow("SETHOMOGRAPHY");
	int i = 0;
	while (i < NO_OF_CAMERAS)
	{
		cout << "Enter the number of points to be marked: ";
		cin >> noOfPoints;
		wrHomography << noOfPoints << " ";
		int planeindex;
		cout << "Enter plane index: ";
		cin >> planeindex;
		wrHomography << planeindex << endl;
		cvShowImage("SETHOMOGRAPHY", images[i]);
		cvSetMouseCallback("SETHOMOGRAPHY", on_mouseHomography, (void*)images[i]);
		cvWaitKey(0);
		i++;
	}
	for (int i = 0; i < NO_OF_CAMERAS; i++)
		cvReleaseCapture(&capture[i]);
	wrHomography.close();
	cvDestroyWindow("SETHOMOGRAPHY");
}

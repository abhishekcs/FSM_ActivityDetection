#include "../include/state.h"
#include "../include/activity.h"
#include "../include/person.h"
#include "../include/dlist.h"
#include "../include/detection.h"
#include "../include/recognition.h"
#include "../include/searchfunctions.h"
#include "../include/init.h"
#include "../include/hierarchy.h"
#include "../include/include.h"
#include "../include/setROI.h"
#include "../include/setHomography.h"
#define CAM0_FPS 15.761570
#define CAM1_FPS 20.062592
#define CAM2_FPS 16.071487
#define CAM3_FPS 15.558937

#define CAM0_DELAY 72
#define CAM1_DELAY 70
#define CAM2_DELAY 68
#define CAM3_DELAY 60

int count0 = 1, count1 = 1, count2 = 1, count3 = 1;
int count0_total = 0, count1_total = 0, count2_total = 0, count3_total = 0;

bool cameraFeed = false;
CvHaarClassifierCascade *cascade;
CvMemStorage *storage;
CvFont font;
int frameCount[NO_OF_CAMERAS];

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		cout << "Usage: " << argv[0] << " [mode] [arguments]\n";
		cout << "possible modes are: run configure query\n"; 
		exit(1);
	}
	else if (argc >= 2)
	{
		if (strcmp(argv[1], "run") == 0)
			goto run;
		else if (strcmp(argv[1], "configure") == 0)
		{
			if (argc == 2)
			{
				cout << "Usage: " << argv[0] << " configure [arguments]\n";
				cout << "possible arguments are: ROI Homography\n"; 
				exit(1);
			}
			else if (strcmp(argv[2], "ROI") == 0)
			{
				setROI(argc-3, argv+3);
				exit(1);
			}
			else if (strcmp(argv[2], "Homography") == 0)
			{
				setHomography(argc-3, argv+3);
				exit(1);
			}
			else
			{
				cout << "Usage: " << argv[0] << " configure [arguments]\n";
				cout << "possible arguments are: ROI Homography\n"; 
				exit(1);
			}
		}
		else if (strcmp(argv[1], "query") == 0)
		{
			cout << "Sorry, feature not available\n";
			exit(1);
		}
		else
		{
			cout << "Usage: " << argv[0] << " [mode] [arguments]\n";
			cout << "possible modes are: run configure query\n"; 
			exit(1);
		}		
	}
	run:
	CvCapture* capture[NO_OF_CAMERAS];
	if (argc == 2)
	{
		cout << "Taking video feed from cameras.\n";
		for (int i = 0; i < NO_OF_CAMERAS; i++)
			capture[i] = cvCaptureFromCAM(i);
		cameraFeed = true;
	}
	else if (argc < NO_OF_CAMERAS+2)
	{
		cout << "Usage: " << argv[0] << " " << "run " << NO_OF_CAMERAS << " video files separated by spaces.\n";
		exit(1);
	} 
	else
	{
		for (int i = 0; i < NO_OF_CAMERAS; i++)
			capture[i] = cvCaptureFromFile(argv[i+2]);
	}
	for (int i = 0; i < NO_OF_CAMERAS; i++)
		ASSERT(capture[i]);
	char haarcascade[100];
	strcpy(haarcascade, PROJECT_PATH);
	strcat(haarcascade, "haarcascades/haarcascade_fullbody.xml");
	cascade = (CvHaarClassifierCascade*)cvLoad(haarcascade);
	ASSERT(cascade);
	storage = cvCreateMemStorage(0);
	ASSERT(storage);
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, 2.0, 2.0, 0, 5);
	PRINT("INITIALISING");
	initHomography();
	PRINT("POST-HOMOGRAPHY");
	initROI();
	PRINT("POST-ROI");
	initActivity();
	PRINT("POST-ACTIVITY");
	for (int i = 0; i < NO_OF_CAMERAS; i++)
	{
		if (cameraFeed)
		{
			char cameraName[10];
			sprintf(cameraName, "%s %d", "camera", i);
			PRINT(cameraName);
			cvNamedWindow(cameraName);
		}
		else
			cvNamedWindow(argv[i+2]);
	}
	for (int i = 0; i < NO_OF_CAMERAS; i++)
		frameCount[i] = 0;
	IplImage *frame;
	/* FORWARDING THE VIDEOS */
	for (int i = 0; i < (int)CAM0_DELAY*CAM0_FPS; i++)
		frame = cvQueryFrame(capture[0]);
	for (int i = 0; i < (int)CAM1_DELAY*CAM1_FPS; i++)
		frame = cvQueryFrame(capture[1]);
	for (int i = 0; i < (int)CAM2_DELAY*CAM2_FPS; i++)
		frame = cvQueryFrame(capture[2]);
	for (int i = 0; i < (int)CAM3_DELAY*CAM3_FPS; i++)
		frame = cvQueryFrame(capture[3]);
	/* FORWARDING DONE */
	while (1)
	{
		/*
		for (int i = 0; i < NO_OF_CAMERAS; i++)
		{
			for (int j = 0; j < runFrames; j++)
			{
				frame = cvQueryFrame(capture[i]);
				ASSERT(frame);
				frame->origin = 0;
				if (cameraFeed)
				{
					char cameraName[10];
					sprintf(cameraName, "%s %d", "camera", i);
					detectBodies(frame, cameraName, i);
				}
				else
					detectBodies(frame, argv[i+2], i);
				cvWaitKey(2);
			}
		}
		*/
		while (count0_total < CAM0_FPS*count0)
		{
			frame = cvQueryFrame(capture[0]);
			ASSERT(frame);
			frame->origin = 0;
			if (cameraFeed)
			{
				char cameraName[10];
				sprintf(cameraName, "%s %d", "camera", 0);
			//	detectBodies(frame, cameraName, 0);
			}
			else
			//	detectBodies(frame, argv[2], 0);
			cvWaitKey(2);
			count0_total++;
		}
		count0++;
		while (count1_total < CAM1_FPS*count1)
		{
			frame = cvQueryFrame(capture[1]);
			ASSERT(frame);
			frame->origin = 0;
			//IplImage* frameResized = cvCreateImage(cvSize(640, 480), frame->depth, frame->nChannels);
			//cvResize(frame, frameResized);
			if (cameraFeed)
			{
				char cameraName[10];
				sprintf(cameraName, "%s %d", "camera", 1);
				//detectBodies(frameResized, cameraName, 1);
				detectBodies(frame, cameraName, 1);
			}
			else
				//detectBodies(frameResized, argv[3], 1);
				detectBodies(frame, argv[3], 1);
			cvWaitKey(2);
			count1_total++;
		}
		count1++;
		while (count2_total < CAM2_FPS*count2)
		{
			frame = cvQueryFrame(capture[2]);
			ASSERT(frame);
			frame->origin = 0;
			if (cameraFeed)
			{
				char cameraName[10];
				sprintf(cameraName, "%s %d", "camera", 2);
				detectBodies(frame, cameraName, 2);
			}
			else
				detectBodies(frame, argv[4], 2);
			cvWaitKey(2);
			count2_total++;
		}
		count2++;
		while (count3_total < CAM3_FPS*count3)
		{
			frame = cvQueryFrame(capture[3]);
			ASSERT(frame);
			frame->origin = 0;
			if (cameraFeed)
			{
				char cameraName[10];
				sprintf(cameraName, "%s %d", "camera", 3);
				detectBodies(frame, cameraName, 3);
			}
			else
				detectBodies(frame, argv[5], 3);
			cvWaitKey(2);
			count3_total++;
		}
		count3++;
	}
	for (int i = 0; i < NO_OF_CAMERAS; i++)
	{
		cvReleaseCapture(&capture[i]);
		if (cameraFeed)
		{
			char cameraName[10];
			sprintf(cameraName, "%s %d", "camera", i);
			cvDestroyWindow(cameraName);
		}
		else
			cvDestroyWindow(argv[i+2]);
	}
	cvReleaseHaarClassifierCascade(&cascade);
	cvReleaseMemStorage(&storage);
	return 1;	
}

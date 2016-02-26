#include "../include/init.h"
#include "../include/hierarchy.h"
#include "../include/activity.h"
#include "../include/detection.h"
#include "../include/person.h"

double *imageCoordinates[NO_OF_CAMERAS];
double *worldCoordinates[NO_OF_CAMERAS];
double homography[NO_OF_CAMERAS][9];
double invHomography[NO_OF_CAMERAS][9];
int worldZs[NO_OF_CAMERAS];
location *ROI[NO_OF_CAMERAS][MAX_ROI];
hierarchy hier;
vector <activity*> ac;
extern person *p[NO_OF_PERSONS];

void initHomography()
{
	char homographypath[60];
	strcpy(homographypath, PROJECT_PATH);
	strcat(homographypath, "files/homography");
	PRINT(homographypath);
	fstream read;
	read.open(homographypath, ios::in);
	ASSERT(read != NULL);
	int noOfCameras;
	read >> noOfCameras;
	ASSERT(noOfCameras == NO_OF_CAMERAS);
	//read >> boxLength;
	//read >> boxWidth;
	//read >> planeWidth;
	CvMat imageMat, worldMat, homographyMat, invHomographyMat;
	for (int i = 0; i < NO_OF_CAMERAS; i++)
	{
		int noOfHomographyPoints = 0;
		read >> noOfHomographyPoints;
		PRINTVAL(noOfHomographyPoints);
		read >> worldZs[i];
		ASSERT(noOfHomographyPoints >= 4);
		imageCoordinates[i] = new double[noOfHomographyPoints*2];
		worldCoordinates[i] = new double[noOfHomographyPoints*2];
		for (int j = 0; j < noOfHomographyPoints; j++)
		{
			read >> imageCoordinates[i][2*j];
			read >> imageCoordinates[i][2*j+1];
			read >> worldCoordinates[i][2*j];
			read >> worldCoordinates[i][2*j+1];
		}
		imageMat = cvMat(noOfHomographyPoints, 2, CV_64FC1, imageCoordinates[i]);
		worldMat = cvMat(noOfHomographyPoints, 2, CV_64FC1, worldCoordinates[i]);
		homographyMat = cvMat(3, 3, CV_64FC1, homography[i]);
		invHomographyMat = cvMat(3, 3, CV_64FC1, invHomography[i]);
		cvFindHomography(&imageMat, &worldMat, &homographyMat, 0, 0, NULL);
		cvInv(&homographyMat, &invHomographyMat, CV_LU);
	}
	read.close();
}

void initROI()
{
	char ROIpath[60];
	strcpy(ROIpath, PROJECT_PATH);
	strcat(ROIpath, "files/ROI");
	PRINT(ROIpath);
	fstream read;
	read.open(ROIpath, ios::in);
	ASSERT(read != NULL);
	int noOfCameras = 0;
	read >> noOfCameras;
	ASSERT(noOfCameras == NO_OF_CAMERAS);
	for (int i = 0; i < NO_OF_CAMERAS; i++)
	{
		int noOfROI = 0;
		read >> noOfROI;
		ASSERT(noOfROI > 1 && noOfROI <= MAX_ROI);
		for (int j = 0; j < noOfROI; j++)
		{
			int imageX, imageY;
			read >> imageX >> imageY;
			float worldX, worldY;
			transform(imageX, imageY, &worldX, &worldY, homography[i]);
			PRINTVAL(worldX);
			PRINTVAL(worldY);
			ROI[i][j] = new location();
			ROI[i][j]->wx = worldX;
			ROI[i][j]->wy = worldY;
			ROI[i][j]->wz = worldZs[i];
			read >> ROI[i][j]->name;		
		}
	}
	read.close();
}

void initActivity()
{
	char activityPath[60];
	strcpy(activityPath, PROJECT_PATH);
	strcat(activityPath, "/files/activity");
	ifstream read;
	read.open(activityPath, ios::in);
	int noOfActivities = 0;
	read >> noOfActivities;
	activity *temp;
	for (int i = 0; i < noOfActivities; i++)
    {
    	cout << "NotDone\n";
    	temp=new activity(read);
        ac.push_back(temp);
        cout << "Done\n";
        hier.addLevel(ac[i]->level);
    	hier.addActivity(ac[i], ac[i]->level);
	}
	for(int j=0;j<NO_OF_PERSONS;j++)
		{
			p[j]=new person(j+1,&hier);
		}
}

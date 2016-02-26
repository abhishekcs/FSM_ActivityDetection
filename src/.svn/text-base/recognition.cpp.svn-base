#include "../include/recognition.h"

int numBins = 256;
float range[] = {0, 255};
float *ranges[] = { range };
personHistogram* database[NO_OF_PERSONS];
extern int frameCount[NO_OF_CAMERAS];
int countDataset = 0;
int noOfPersons;

personHistogram::personHistogram()
{
	currHistograms = 0;
	for (int i = 0; i < MAX_HISTOGRAMS; i++)
		noOfMatches[i] = 0;
}

int findMinIndex(int *p, int len)
{
	int index = 0;
	for (int i = 0; i < len-1; i++)
	{
		if (p[i+1] < p[i])
			index = i+1;
	}
	return index;
}

int findMaxCompare(personHistogram *p, CvHistogram *histA, CvHistogram *histB, int len)
{
	int index = 0;
	float compareMax = 0.0;
	for (int i = 0; i < len; i++)
	{
		float compareA = cvCompareHist(histA, p->A[i], 3);
        float compareB = cvCompareHist(histB, p->B[i], 3);            	
        float compare = (compareA+compareB)/2;
		if (compare > compareMax)
		{
			compareMax = compare;
			index = i;
		}
	}
	return index;
}

int recognition(IplImage *inc_image, int cameraIndex)
{
	ASSERT(inc_image);
	//IplImage* temp_image = cvCreateImage(cvSize(52, 208), inc_image->depth, inc_image->nChannels);	
	IplImage* temp_image = cvCreateImage(cvSize(inc_image->width, inc_image->height), inc_image->depth, inc_image->nChannels);
	cvResize(inc_image, temp_image);
    fstream wr;
    char recognitionpath[60];
    strcpy(recognitionpath, PROJECT_PATH);
    strcat(recognitionpath, "logs/recognition");
    sprintf(recognitionpath, "%s_%d", recognitionpath, cameraIndex);
    //PRINT(recognitionpath);
    wr.open(recognitionpath, ios::in | ios::out | ios::app);
    wr << "--------------------FRAME " << frameCount[cameraIndex] << "--------------------\n";
    IplImage *test_image = cvCreateImage(cvSize(temp_image->width,temp_image->height),temp_image->depth,temp_image->nChannels);                                            	
    CvHistogram *histA = cvCreateHist(1, &numBins, CV_HIST_ARRAY, ranges, 1);
    CvHistogram *histB = cvCreateHist(1, &numBins, CV_HIST_ARRAY, ranges, 1);
    cvClearHist(histA);
    cvClearHist(histB);
    IplImage* imgA = cvCreateImage(cvGetSize(temp_image), 8, 1);
    IplImage* imgB = cvCreateImage(cvGetSize(temp_image), 8, 1);
    cvCvtColor(temp_image, test_image, CV_BGR2Lab);
    //cvCvtColor(temp_image, test_image, CV_BGR2HSV);
    cvSplit(test_image, NULL, imgA, imgB, 0);
    //cvSplit(test_image, imgA, imgB, NULL, 0);
    if (GENERATE_DATASET)
    {
    	char datasetpath[60];
    	strcpy(datasetpath, PROJECT_PATH);
    	strcat(datasetpath, "dataset/body");
        char count_data_str[5];
        sprintf(count_data_str, "%d %d", cameraIndex, countDataset);
        strcat(datasetpath, count_data_str);
        strcat(datasetpath, ".jpg");
        //PRINT(datasetpath);
        cvSaveImage(datasetpath, temp_image);
        countDataset++;
    }
    cvCalcHist(&imgA, histA, 0, 0);
    cvNormalizeHist(histA, 1.0);
 	cvCalcHist(&imgB, histB, 0, 0);
    cvNormalizeHist(histB, 1.0);
    ASSERT(histA && histB);
	//PRINT("Histogram Calculation Over");
 	int perIndex = 0;
    if (noOfPersons == 0)
    {
    	database[noOfPersons] = new personHistogram(); 
		database[noOfPersons]->A[database[noOfPersons]->currHistograms] = histA;
		database[noOfPersons]->B[database[noOfPersons]->currHistograms] = histB;
		database[noOfPersons]->noOfMatches[database[noOfPersons]->currHistograms] = 1;
		database[noOfPersons]->currHistograms++;
        noOfPersons++;
        wr << "NEW PERSON DETECTED\n"; 
    }
    else
    {
    	int hitPerIndex = -1;
    	int hitHisIndex = -1;
    	int weakPerIndex = -1;
    	float minHitCompare = 1.0;
    	float minWeakCompare = 1.0;
        for (int i = 0; i < noOfPersons; i++)
        {
        	for (int j = 0; j < database[i]->currHistograms; j++)
        	{
            	float compareA = cvCompareHist(histA, database[i]->A[j], 3);
            	float compareB = cvCompareHist(histB, database[i]->B[j], 3);
            	float compare = (compareA+compareB)/2;
            	if (compare < EXTREME)
            	{
            		database[i]->noOfMatches[j]++;
            		if (compare < minHitCompare)
            		{ 
            			hitPerIndex = i;
            			hitHisIndex = j;
						minHitCompare = compare;
					}
					wr << "Person " << (i+1) << "Histogram " << (j+1) << "HIT " << compare << "\n";
            	}
            	else if (compare < DIFFERENT)
            	{
					if (compare < minWeakCompare)
					{
						weakPerIndex = i;
						minWeakCompare = compare;
					}
					wr << "Person " << (i+1) << "Histogram " << (j+1) << "WEAK " << compare << "\n";
            	}
            	else
            		wr << "Person " << (i+1) << "Histogram " << (j+1) << "MISS " << compare << "\n";
            }
        }
        if (hitPerIndex != -1)
        {
        	database[hitPerIndex]->A[hitHisIndex] = histA; 	// Here to insert average of histograms
        	database[hitPerIndex]->B[hitHisIndex] = histB;
        	perIndex = hitPerIndex;
        }
		else if (weakPerIndex != -1)
		{
			if (database[weakPerIndex]->currHistograms < MAX_HISTOGRAMS)
            {
            	database[weakPerIndex]->A[database[weakPerIndex]->currHistograms] = histA;
            	database[weakPerIndex]->B[database[weakPerIndex]->currHistograms] = histB;
            	database[weakPerIndex]->noOfMatches[database[weakPerIndex]->currHistograms]++;
            	database[weakPerIndex]->currHistograms++;
            }
            else
            {
            	//int minIndex = findMinIndex(database[weakPerIndex]->noOfMatches, MAX_HISTOGRAMS);
            	int minIndex = findMaxCompare(database[weakPerIndex], histA, histB, MAX_HISTOGRAMS);
            	wr << "Histogram Removed " << (minIndex+1) << "\n"; 
            	database[weakPerIndex]->A[minIndex] = histA;
            	database[weakPerIndex]->B[minIndex] = histB;
            	database[weakPerIndex]->noOfMatches[minIndex] = 1;
            }
            perIndex = weakPerIndex;
		}
		else
		{     
       		if (noOfPersons == NO_OF_PERSONS)
        	{
        		printf("No of persons exceeded %d ... exiting.\n", NO_OF_PERSONS);
        		exit(1); 
        	}
        	else
        	{
        		database[noOfPersons] = new personHistogram();
        		database[noOfPersons]->A[database[noOfPersons]->currHistograms] = histA;
        		database[noOfPersons]->B[database[noOfPersons]->currHistograms] = histB;
        		database[noOfPersons]->noOfMatches[database[noOfPersons]->currHistograms] = 1;
        		database[noOfPersons]->currHistograms++;
				perIndex = noOfPersons;
				noOfPersons++;
				wr << "NEW PERSON DETECTED\n";
			}
        }
    }
    wr.close();
    return perIndex;
}

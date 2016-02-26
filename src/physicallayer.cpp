#include "../include/physicallayer.h"
#include "../include/searchfunctions.h"
#include "../include/dlist.h"
#include "../include/init.h"
#include "../include/person.h"
#include "../include/hierarchy.h"

extern hierarchy hier;
extern int worldZs[NO_OF_CAMERAS];
extern location *ROI[NO_OF_CAMERAS][MAX_ROI];
extern person *p[NO_OF_PERSONS];
extern int noOfPersons;

int findROIindex(float x, float y, int cameraIndex)
{
	PRINT("--------------ROI-------------------");
	PRINTVAL(x);
	PRINTVAL(y);
	int minIndex = 0;
	float minDis = numeric_limits<float>::infinity();
	int i = 0;
	while (ROI[cameraIndex][i] != NULL)
	{
		float wx = ROI[cameraIndex][i]->wx;
		float wy = ROI[cameraIndex][i]->wy;
		float dis = pow((wx-x),2)+pow((wy-y),2);
		if (dis < minDis)
		{
			minIndex = i;
			minDis = dis;
		}
		i++;
	}
	PRINTVAL(ROI[cameraIndex][minIndex]->wx);
	PRINTVAL(ROI[cameraIndex][minIndex]->wy);
	return minIndex;
}

int findROI(int pi,float x, float y, float vx, float vy,  int cameraIndex)
{
	int minIndex = 0;
	float maxDot = 0;
	float vm=pow(pow((vx),2)+pow((vy),2),0.5);
	char physicallayerpath[60];
	strcpy(physicallayerpath, PROJECT_PATH);
	strcat(physicallayerpath, "logs/commentary");
	fstream wr;
	wr.open(physicallayerpath, ios::in | ios::out | ios::app);
	vx = vx/vm;
	vy = vy/vm;
	int i = 0;
	int j;
	while (ROI[cameraIndex][i] != NULL)
	{
		j=p[pi]->search(cameraIndex,i);
		float wx = ROI[cameraIndex][i]->wx;
		float wy = ROI[cameraIndex][i]->wy;
		float xr = x-wx;
		float yr = y-wy;
		float rm = pow(pow((xr),2)+pow((yr),2),0.5);
		xr = xr/rm;
		yr = yr/rm;
		if(xr >= EPSI || xr <= (-EPSI))
		{
			if(j==-1)
			{
				p[pi]->shift();
				p[pi]->ROI_zone[NO_OF_ZONES].cameraInd = cameraIndex;
				p[pi]->ROI_zone[NO_OF_ZONES].ROI_no = i;
				p[pi]->ROI_zone[NO_OF_ZONES].sign = sg(yr);
				p[pi]->ROI_zone[NO_OF_ZONES].appear = true;
			}
			else
			{
				zone* z = &(p[pi]->ROI_zone[j]);
				if(z->appear == true)
				{
					if(z->sign != sg(yr))
					{
						wr << "Person " << pi << " just crossed ROI " << i << " of camera " << cameraIndex << "\n";
					}
					z->appear = false;
				}
				else
				{
					z->appear = true;
					z->sign = sg(yr);
				}
			}
		}
		float cos_dist = xr*vx+yr*vy;
		if (cos_dist > maxDot)
		{
			minIndex = i;
			maxDot = cos_dist;
		}
		i++;
	}
	wr.close();
	return minIndex;
}

void personUpdate(vector<int> peopleRecognised, vector<float> worldXs, vector<float> worldYs, int cameraIndex, int frameNumber)
{
	PRINT("personUpdate");
	char physicallayerpath[60];
	strcpy(physicallayerpath, PROJECT_PATH);
	strcat(physicallayerpath, "logs/physicallayer");
	fstream wr;
	wr.open(physicallayerpath, ios::in | ios::out | ios::app);
	wr << setprecision(2);
	for (int i = 0; i < noOfPersons; i++)
	{
		int index = linearsearch(peopleRecognised, i);
		if (index == -1)
		{
		}
		else
		{
			if (p[i] == NULL)
			{
				p[i] = new person(i, &hier);
				int ROIindex = findROIindex(worldXs[index], worldYs[index], cameraIndex);
				p[i]->pastLocRecord.insertBack(worldXs[index], worldYs[index], worldZs[cameraIndex], frameNumber);
				wr << "Person " << (i+1) << " exited from ROI " << ROI[cameraIndex][ROIindex]->name << "." << endl;
				p[i]->visible = true;
				p[i]->latency = 0;
				p[i]->visibleCameraIndex = cameraIndex; 
				p[i]->update(frameNumber, cameraIndex, ROIindex, false);
			}
			else
			{
				if (p[i]->visible == false)
				{
					int ROIindex = findROIindex(worldXs[index], worldYs[index], cameraIndex);
					wr << "Person " << (i+1) << " exited from ROI " << ROI[cameraIndex][ROIindex]->name << "." << endl;
					p[i]->latency = 0;
					p[i]->visibleCameraIndex = cameraIndex;
					p[i]->update(frameNumber, cameraIndex, ROIindex, false);
				}
				p[i]->visibleCameraIndex = cameraIndex;	
				int size = p[i]->pastLocRecord.getsize();
				PRINTVAL(size);
				if (size < MAX_PAST_RECORDS)
				{
					PRINTVAL(index);
					PRINTVAL(worldXs[index]);
					PRINTVAL(worldYs[index]);
					p[i]->pastLocRecord.insertBack(worldXs[index], worldYs[index], worldZs[cameraIndex], frameNumber);
				}
				else
				{
					p[i]->pastLocRecord.removeFront();
					p[i]->pastLocRecord.insertBack(worldXs[index], worldYs[index], worldZs[cameraIndex], frameNumber);		
				}
				p[i]->visible = true;
				size = p[i]->pastLocRecord.getsize();
				if (p[i]->walking_count % PHYSICAL_LAYER_TR == 0)
				{
					if (size > AVERAGING_FRAMES*2)
					{
						float avgIniX = 0.0, avgIniY = 0.0, avgFinX = 0.0, avgFinY = 0.0;
						node *trav1 = p[i]->pastLocRecord.front;
						node *trav2 = p[i]->pastLocRecord.back;
						for (int k = 0; k < AVERAGING_FRAMES; k++)
						{
							avgIniX += trav1->wx;
							avgIniY += trav1->wy;
							avgFinX += trav2->wx;
							avgFinY += trav2->wy;
							trav1 = trav1->next;
							trav2 = trav2->prev;						
						}		
						avgIniX = avgIniX/AVERAGING_FRAMES;
						avgIniY = avgIniY/AVERAGING_FRAMES;
						avgFinX = avgFinX/AVERAGING_FRAMES;
						avgFinY = avgFinY/AVERAGING_FRAMES;
						wr << "Person " << (i+1) << " walking in" << "\t" << (avgFinX-avgIniX)/(size-AVERAGING_FRAMES)*10 << "\t" << (avgFinY-avgIniY)/(size-AVERAGING_FRAMES)*10 << "\t" <<  "direction." << endl; 
					}
				}
				p[i]->walking_count++;
			}
		}
		if (p[i] != NULL && p[i]->visible == true)
		{
			//if ((frameNumber-p[i]->pastLocRecord.back->frameIndex) > MAX_LATENCY)
			if (p[i]->latency > MAX_LATENCY && p[i]->visibleCameraIndex == cameraIndex)
			{
				int ROIindex = findROIindex(p[i]->pastLocRecord.back->wx, p[i]->pastLocRecord.back->wy, cameraIndex);	
				wr << "Person " << (i+1) << " entered in ROI " << ROI[cameraIndex][ROIindex]->name << "." << endl;
				p[i]->pastLocRecord.deleteall();
				p[i]->visible = false;
				p[i]->update(frameNumber, cameraIndex, ROIindex, true);
			}
			else if (p[i]->visibleCameraIndex == cameraIndex)
				p[i]->latency++;
		}
	}
	wr.close();
}

#ifndef PERSON_H
#define PERSON_H

#include<iostream>
#include<fstream>
#include<vector>
#include "hierarchy.h"
#include "state.h"
#include "dlist.h"
#include "include.h"

#define NO_STATE -3
#define NO_OF_ZONES 2

//vector <int> ROzone(2);
	
class pers_st
{
    public:
    state *st;
    int cancel;
    vector<bool> poss;
    
    pers_st(int n);
};

class zone
{
	public:
	int cameraInd;
	int ROI_no;
	bool appear;
	char sign;
};

class person
{
	public:
	zone ROI_zone[NO_OF_ZONES];
	int id;
	bool call;
	int cs;
	int time;
	int cn;
	dlist pastLocRecord;
	hierarchy *h;
	bool visible;
	int walking_count;
	int latency;
	int visibleCameraIndex;
	vector<vector<int> > vic;
	vector<vector<pers_st*> > ac_st;
	//
	person(int ID, hierarchy *h);
	void extraLevel(int l);
	int search(int cameraIndex,int ROI_in);
	void shift();
	void extraActivity(int lev);
	void update(int frame_no, int ROI_i, int ROI_j, bool enter);
	void update_fsm(int id, int frame_no);
};

#endif

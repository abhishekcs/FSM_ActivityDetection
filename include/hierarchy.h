#ifndef HIERARCHY_H
#define HIERARCHY_H

#include<iostream>
#include<vector>
#include "activity.h"
#include "include.h"

class hierarchy
{
    public:
    vector<int> alloted;
    int noOfLevels;
    vector<vector <activity*> > hier_of_ac;
    
    hierarchy();
    void addLevel(int l);
    void addActivity(activity *a, int level);
};

#endif

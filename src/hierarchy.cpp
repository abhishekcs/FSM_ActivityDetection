#include "../include/hierarchy.h"

hierarchy::hierarchy()
{
   	noOfLevels = 0;
}
    
void hierarchy::addLevel(int l)
{
	while (noOfLevels <= l)
   	{
   		hier_of_ac.push_back(vector<activity*> ());
    	alloted.push_back(0);
    	noOfLevels++;
    }
}
        
void hierarchy::addActivity(activity *a, int level)
{
    ASSERT(level < noOfLevels && (level >= 0));
    hier_of_ac[level].push_back(a);
    alloted[level] += 1;
}

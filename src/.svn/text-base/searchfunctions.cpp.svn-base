#include "../include/searchfunctions.h"

int bisearch(vector<int> A, int le, int ri, int ele)
{
    int present = -1;
    int l = le;
    int h = ri;
    int mid = 0;
    while (l <= h)
    {
        mid = (l+h)/2;
        if (A[mid] == ele)
        {
            present = mid;
            break;
        } 
        else if (A[mid] > ele) 
        	h = mid-1;
        else 
        	l = mid+1;
    }
    return present;
}

int bsearch(vector<state*> A, int le, int ri, int ele)
{
    int present = -1;
    int mid = le;
    while (mid <= ri)
    {
        if (A[mid]->sid == ANY_STATE)
        {
            return(mid);
        }
        if (A[mid]->belongs_current(ele))
        {
            present = mid;
            break;
        }
    	mid = mid+1;
    }
    return present;
}

int linearsearch(vector<int> vec, int j)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == j)
			return i;
	}
	return -1;
}

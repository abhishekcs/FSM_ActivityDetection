#ifndef SEARCHFUNCTIONS_H
#define SEARCHFUNCTIONS_H

#include<iostream>
#include<vector>
#include "state.h"
#include "include.h"

#ifndef ANY_STATE
#define ANY_STATE -2
#endif

int bisearch(vector<int> A, int le, int ri, int ele);
int bsearch(vector<state*> A, int le, int ri, int ele);
int linearsearch(vector<int> vec, int j);

#endif

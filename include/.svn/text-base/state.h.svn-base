#ifndef STATE_H
#define STATE_H

#include<iostream>
#include<vector>
#include "include.h"

#ifndef ANY_STATE
#define ANY_STATE -2
#endif

class state
{
    public:
    int sid;
    int num_next_st;
    int time;
    char status;
    vector<state*> next;
    vector<int> cur;
    
    state();
    bool noOfNext();
    state* isNext(int s, int t);
    bool belongs_current(int s);
};

#endif

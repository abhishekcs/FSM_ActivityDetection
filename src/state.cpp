#include "../include/state.h"
#include "../include/searchfunctions.h"

state::state()
{
}
    
bool state::noOfNext()
{
    bool b = false;
    int n = next.size();
    for (int i = 0; i < n; i++)
    {
        if (next[i]->sid == ANY_STATE)
        {
            b = true;
            break;
        }
        else
            num_next_st += next[i]->cur.size();
    }
  	return b;
}
    
state* state::isNext(int s, int t)
{
    int n = next.size();
    int i = bsearch(next, 0, n-1, s);
    if (i >= 0)
        return next[i];
    else
        return NULL;
}
    
bool state::belongs_current(int s)
{
  	return (bisearch(cur, 0, cur.size()-1, s) != -1);
}

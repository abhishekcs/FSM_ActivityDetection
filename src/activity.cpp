#include "../include/activity.h"

activity::activity(ifstream& read)
{
   	state *temp;
   	int nob, sta, noc, succ;
   	int i, j;
   	if (!read)
       	cout << "Not Opening \n";
   	read >> ts;
   	read >> ss;
   	read >> level;
   	cout << "hiiii\n";
   	for (i = 0; i < ts; i++)
   	{
       	temp = new state();
       	st_arr.push_back(temp);
   	}
   	for (i = 0; i < ts; i++)
   	{
       	read >> noc;
       	read >> st_arr[i]->sid;
       	for (j = 0; j < noc; j++)
       	{
           	read >> sta;
           	st_arr[i]->cur.push_back(sta);
       	}
       	st_arr[i]->time = 0;
       	read >> nob;
       	for (j = 0; j < nob; j++)
       	{
           	read >> sta;
           	st_arr[i]->next.push_back(st_arr[sta]);
       	}
       	read >> succ;
       	if (succ == 1)
       	{
       	    st_arr[i]->status = 's';
       	}
   	}
   	head = new state();
   	head->sid = -1;
   	head->cur.push_back(-1);
   	head->status = 'i';
   	for (j = 0; j < ss; j++)
   	    (head->next).push_back(st_arr[j]);
   	if ((head->noOfNext()) == true)
   	    head->num_next_st = ts;
   	for (i = 0; i < ts; i++)
   	{
   	    if ((st_arr[i]->noOfNext()) == true)
   	        st_arr[i]->num_next_st = ts;    
   	}
   	cout <<"ggg \n";
}

extern vector <activity*> ac;

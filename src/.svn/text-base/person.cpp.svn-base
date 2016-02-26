#include "../include/person.h"
#include<cstring>

pers_st::pers_st(int n)
{
   	cancel = 0;
    for (int i = 0; i < n; i++)
   	    poss.push_back(true);
}     

person::person(int ID, hierarchy *hi)
{
	h = hi;
	visible = false;
	walking_count = 0;
   	id = ID;
   	cs = NO_STATE;
   	call = true;
   	time = 0;
   	for (int j = 0; j < h->noOfLevels; j++)
   	{
   	    ac_st.push_back(vector<pers_st*> ());
   	    vic.push_back(vector<int> ());
   	    for(int i = 0; i < h->alloted[j]; i++)
   	    {
   	        vic[j].push_back(0);
   	        if (j == 0)
   	        {
   	        	pers_st *p = new pers_st(h->hier_of_ac[j][i]->ts);
   	        	p->st = h->hier_of_ac[j][i]->head;
   	        	ac_st[j].push_back(p);
   	        }
   	        else
           	{
           		pers_st *p = new pers_st(h->alloted[j-1]);
           		p->st = h->hier_of_ac[j][i]->head;
           		ac_st[j].push_back(p);
           	}
       	}
   	}
   	for(int i=0;i<NO_OF_ZONES;i++)
   	{
		ROI_zone[i].cameraInd=-1;
		ROI_zone[i].ROI_no=-1;
		ROI_zone[i].sign='-';
		ROI_zone[i].appear=false;   
	}
}

void person::extraLevel(int l)
{
	while(ac_st.size() <= l)
	{
		ac_st.push_back(vector<pers_st*> ());
   		vic.push_back(vector<int> ());
   	}
}

void person::extraActivity(int lev)
{
	vic[lev].push_back(0);
	int l = h->alloted[lev];
    if (lev == 0)
    {
        pers_st *p = new pers_st(h->hier_of_ac[lev][l]->ts);
        p->st = h->hier_of_ac[lev][l]->head;
        ac_st[lev].push_back(p);
    }
    else
    {
        pers_st *p = new pers_st(h->alloted[lev-1]);
        p->st = h->hier_of_ac[lev][l]->head;
        ac_st[lev].push_back(p);
    }
}
	
int person::search(int cameraIndex,int ROI_in)
{
int i=0;
for (i=0;i<NO_OF_ZONES;i++)
{
	if(cameraIndex==ROI_zone[i].cameraInd && ROI_in==ROI_zone[i].ROI_no)
		return i;
}
return -1;
}

void person::shift()
{
	int i=0;
	for(i=0;i<NO_OF_ZONES-1;i++)
		ROI_zone[i]=ROI_zone[i+1];
}	
void person::update(int frame_no, int ROI_i, int ROI_j, bool enter)
{
   	cs = MAX_ROI*ROI_i+ROI_j;
    if (call == true)
        update_fsm(id, frame_no);
    call = not(enter);
}
	
void person::update_fsm(int id, int frame_no)
{
   	state *temp;
   	char s;
   	ofstream o;
   	int i = 0, j = 0, k = 0, l = 0;
   	char activityLogPath[60];
   	strcpy(activityLogPath, PROJECT_PATH);
   	strcat(activityLogPath, "/logs/higherlayers");
   	o.open(activityLogPath, ios::app);
   	o << "Person " << id << " State " << cs << "\n";
   	for (i = 0; i < h->alloted[0]; i++)
   	{
       	//havent allowed input alphabet till now 
       	if (!((temp = ((ac_st[0][i]->st)->isNext(cs, time))) == NULL))
       	{
       	    s = temp->status;
       	    if (s == 's')
       	    {
       	        vic[0][i]++;
       	        o << "Person " << id << " Frame Number " << frame_no << " just did activity " << "0 " << i << " Total activity count " << vic[0][i] << "\n";
       	    }
       	    ac_st[0][i]->st = temp;
           	time = 0; 
       	}
       	else 
       	{
           	time = 0;
           	ac_st[0][i]->st = h->hier_of_ac[0][i]->head;
       	}
   	}
   	int flag = 0;
   	for (i = 1; i < h->noOfLevels; i++)
   	{
       	for (j = 0; j < h->alloted[i]; j++)
       	{
           	flag = 0;
           	for (k = 0; k < h->alloted[i-1]; k++)
           	{
           	    temp = ((ac_st[i][j]->st)->isNext(k, time));
           	    if ((ac_st[i-1][k]->st->status == 's') && (!(temp == NULL)) && (ac_st[i][j]->poss[k] == true))
           	    {
       	            s = temp->status;
       	            if (s == 's')
       	            {
                        //Remember that success can also branch
                        vic[i][j]++;
                            o << "Person " << id << " just did activity " << i << " " << j << " Total activity count " << vic[0][i] << "\n";
                    }
                    ac_st[i][j]->st = temp;
                    ac_st[i][j]->cancel = 0;
                    for (l = 0; l < h->alloted[i-1]; l++)
                        ac_st[i][j]->poss[l] = true;
                    time = 0;
                    break;
                }
            }
            if (flag == 1)
            {
               	ac_st[i][j]->st = h->hier_of_ac[i][j]->head;
               	for (l = 0; l < h->alloted[i-1]; l++)
                {
                  	ac_st[i][j]->poss[l] = true;
                }
              	ac_st[i][j]->cancel = 0;
            }
        }
    }
    o.close();
}

person *p[NO_OF_PERSONS];

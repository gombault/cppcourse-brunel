#include <iostream>
#include <fstream>
#include "network.h"
using namespace std;

int main()
{
    int T_stop(2000); // time where the simulation ends 
    int simtime(0); // simulation time
    
    /****************************************************************
     *  to display the per cent of the simulation done 
     ******************************************************************/
    
    int progress(1);
    int progress_rate(0.01*T_stop);
    
    /****************************************************************
     *  creating the network with the connections between neurons
     ******************************************************************/
    
    
	Network network;
    network.fill_connection();
    
    /*****************************************************************
     *  for each step we update the network amd increment simtime
     ******************************************************************/
    
    while(simtime < T_stop)
    {

		if(simtime > progress_rate)
		{
			cout << progress << "%" << endl;
			progress += 1;
			progress_rate += 0.01*T_stop;
		}
	
	    network.update(simtime);
	    ++ simtime;   
	}
	
	
}


#include <iostream>
#include <fstream>
#include "network.h"
using namespace std;

int main()
{
	cout << "akljsdf" << endl;
    double T_stop(5000); // time where the simulation ends
    int h =1;
    int simtime(0); // simulation time
    
    int progress(1);
    int progress_rate(0.01*T_stop);
    
	Network network;
    network.fill_connection();
    
    
    while(simtime < T_stop)
    {
		//cout << "abababa" << endl;
		if(simtime > progress_rate)
		{
			cout << progress << "%" << endl;
			progress += 1;
			progress_rate += 0.01*T_stop;
		}
	
	    network.update();
	    simtime +=h;
	}
	
	
}


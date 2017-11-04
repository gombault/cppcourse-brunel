#include <iostream>
#include "network.h"
#include <vector>
#include <cmath>
#include <fstream>
#include <random>
using namespace std;

Network :: Network () 
        {
			Ntot=12500;
		    Ne=10000;
			Ni=2500;
			Ce=1000;
			Ci=250;
			Je=0.1;
			Ji=-0.45;
			 for (int i=0; i<Ntot; ++i) // initialisation of connections vector to 0 
			 {
				 vector<double> a(Ntot,0);
				 connection.push_back(a);
			 }
			 
			 for (int i=0; i<Ntot; ++i) // creation of neurons in tab_neuron 
			 {
				 tab_neuron.push_back(Neuron());
			 }
			 
		}
		
void Network :: fill_connection()
 {
	 for(int i=0; i<Ne; ++i) // we go through the vecror of connections verticaly 
      {
		  static random_device rd; //random law
	      static mt19937 gen(rd());
	      static uniform_int_distribution<> connection_from(0,Ne-1); // to chose randomly betwenn 0 and 10000 which excitatory neurons will have connections 
	
		 for(int j=0; j<Ce; ++j) // we go through the vecror horizontally first on the  10000 cases for the  10000 excitatory neurons 
		 {
			  connection[connection_from(gen)][i]+=Je; // we fill connection tab in the index given by the random law
			 
		  }
	  }
	  
	  for(int i=Ne; i<Ntot; ++i) // we go through the vecror of connections verticaly 
	  {
		  static random_device rd;
	      static mt19937 gen(rd());
	      static uniform_int_distribution<> connection_from(Ne,Ntot-1); // to chose randomly betwenn 10000 and 12500 which inhibithory neurons will have connections
	      
		  for(int h=0; h<Ci; ++h) // then we go through the vector on the last 2500 cases for the inhibithory neurons 
		  {
			 connection[connection_from(gen)][i]+=Ji; // we fill connection tab in the index given by the random law
		  }
	 }
 }
 
void Network :: update(int time)
{
	
	ofstream fichier("Spikes.gdf", ios::out | ios::app); // we create a fold to make the plot 

	for(int i=0; i<Ntot; ++i) 
	{
		tab_neuron[i].update(0,time); // we update every neurons of the tab_neuron 

		if(tab_neuron[i].getV()>20.0) //if the neuron spike, it looks at all his connections 
		{
			if(time>10000)
			{
				fichier << time << "	"<< i << endl; 
			}
				
			for(int j=0; j<Ntot; ++j)
			{
				if(connection[i][j]!=0) // we look with which neurons the spiking one is connected 
				{
					tab_neuron[j].receive_spike(connection[i][j]); // each connected neurons receive what is in their buffer 
				}
			}
		}
	}
	
	fichier.close();
}	


 

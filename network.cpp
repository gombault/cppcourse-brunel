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
			Ji=-0.5;
			 for (int i=0; i<Ntot; ++i) /*!<initialisation of connections vector a 0 */
			 {
				 vector<double> a(Ntot,0);
				 connection.push_back(a);
			 }
			 
			 for (int i=0; i<Ntot; ++i) /*!< creation of neurons in tab_neuron */
			 {
				 tab_neuron.push_back(Neuron());
			 }
			 
		}
		
void Network :: fill_connection()
 {
	 for(int i=0; i<12500; ++i) /*!< we go through the vecror of connections verticaly */
	 {
		 for(int j=0; j<0.1*Ne; ++j) /*! < we go through the vecror horizontally first on the  10000 cases for the  10000 excitatory neurons */
		 {
			  connection[random(0,Ne)][i]+=Je;
		  }
		  for(int h=0; h<0.1*Ni; ++h) /*! then we go through the vector on the last 2500 cases for the inhibithory neurons */
		  {
			 connection[random(Ne,Ntot)][i]+=Ji;
		  }
	 }
 }
void Network :: update(int time)
{
	
	ofstream fichier("Spikes.gdf", ios::out | ios::app); /*!< we create a fold to make the plot */ 
	
	 /*****************************************************************************************//**
     *    for excitatory neurons 
     ****************************************************************************************/

	for(int i=0; i<Ne; ++i) 
	{
		tab_neuron[i].update(0,time); /*!< we update every neurons of the tab_neuron */

		if(tab_neuron[i].getV()>20.0) /*!< if the neuron spike, it sends Je to all his connections if he is excitatory and Ji if he is inhibitory */
		{
			fichier << time << "	"<< i << endl;
			 
			for(int j=0; j<Ntot; ++j)
			{
				if(connection[i][j]!=0)
				{
					tab_neuron[j].receive_spike(Je);
				}
			}
		}
	}
	
	/*****************************************************************************************//**
     *    for inhibithory neurons 
     ****************************************************************************************/

	for(int i=Ne; i<Ntot; ++i) 
	{
		tab_neuron[i].update(0,time);
		
		if(tab_neuron[i].getV()>20)
		{
			fichier << time << " " << i << endl; 
			
			for(int j=0; j<Ntot; ++j)
			{
				if(connection[i][j]!=0)
				{
					tab_neuron[j].receive_spike(Ji);
				}
			}
		}
	}
	
	fichier.close();
}	

 
int Network :: random(int start, int end)
{
	static random_device rd;
	static mt19937 gen(rd());
	static uniform_int_distribution<> connection_from(start,end-1);
	return connection_from(gen);
}

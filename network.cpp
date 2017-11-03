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
			 for (int i=0; i<Ntot; ++i) /*!<initialisation of connections vector to 0 */
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
			  connection[random(0,Ne)][i]+=Je; /*!< we call random to chose randomly betwenn 0 and 10000 which excitatory neurons will have connections */
		  }
		  for(int h=0; h<0.1*Ni; ++h) /*! then we go through the vector on the last 2500 cases for the inhibithory neurons */
		  {
			 connection[random(Ne,Ntot)][i]+=Ji; /*!< we call random to chose randomly betwenn 10000 and 2500 which inhibitory neurons will have connections */
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
		tab_neuron[i].update(0,time); /*!< we update every exitatory neurons of the tab_neuron */

		if(tab_neuron[i].getV()>20.0) /*!< if the neuron spike, it sends Je to all his connections */
		{
			fichier << time << "	"<< i << endl;
			 
			for(int j=0; j<Ntot; ++j)
			{
				if(connection[i][j]!=0) /*!< we look with which neurons the spiking one is connected */
				{
					tab_neuron[j].receive_spike(Je); /*!< each connected neurons receive Je in their buffer */
				}
			}
		}
	}
	
	/*****************************************************************************************//**
     *    for inhibithory neurons (in the tab_neuron, from 10000 to 12500
     ****************************************************************************************/

	for(int i=Ne; i<Ntot; ++i) 
	{
		tab_neuron[i].update(0,time);   /*!< we update every inhibitory neurons of the tab_neuron */
		
		if(tab_neuron[i].getV()>20)   /*!< if the neuron spike, it sends Ji to all his connection */
		{
			fichier << time << "     " << i << endl; 
			
			for(int j=0; j<Ntot; ++j)  /*!< we look with which neurons the spiking one is connected */
			{
				if(connection[i][j]!=0)
				{
					tab_neuron[j].receive_spike(Ji);  /*!< each connected neurons receive Ji in their buffer */
				}
			}
		}
	}
	
	fichier.close();
}	

/*****************************************************************************************//**
     *    fonction that chose randomly number in a interval to fill the connections tab
     ****************************************************************************************/
 
int Network :: random(int start, int end)
{
	static random_device rd;
	static mt19937 gen(rd());
	static uniform_int_distribution<> connection_from(start,end-1);
	return connection_from(gen);
}

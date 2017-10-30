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
			Ji=0.5;
			g=5;
			J=0.1;
			g=-0.5;
			 for (int i=0; i<Ntot; ++i) //initialisation du tableau de connection a 0
			 {
				 vector<double> a(Ntot,0);
				 connection.push_back(a);
			 }
			 
			 for (int i=0; i<Ntot; ++i) // creation des neurons dans mon tableau de neuron
			 {
				 tab_neuron.push_back(Neuron());
			 }
			 
		}
		
void Network :: fill_connection()
 {
	 for(int i=0; i<12500; ++i) // on itere le long du tableau verticalement
	 {
		 for(int j=0; j<0.1*Ne; ++j) // on itere le long du tableau horizontalement d'abbord sur les 10000 premieres cases pour les 10000 excitatory neurons
		 {
			  connection[random(0,Ne)][i]+=J;
		  }
		  for(int h=0; h<0.1*Ni; ++h) // puis on itere sur les 2500 dernieres cases pour les neurons inhibiteurs
		  {
			 connection[random(Ne,Ntot)][i]+=g;
		  }
	 }
 }
void Network :: update()
{
	
	for(int i=0; i<Ne; ++i) 
	{
		tab_neuron[i].update(0,0,0);
		if(tab_neuron[i].update(0,0,0))
		{
			for(int j=0; j<Ntot; ++j)
			{
				if(connection[i][j]!=0)
				{
					tab_neuron[j].receive_spike(tab_neuron[i].getT_Clock(),J);
				}
			}
		}
	}
	for(int i=Ne; i<Ntot; ++i) 
	{
		tab_neuron[i].update(0,0,0);
		if(tab_neuron[i].update(0,0,0))
		{
			for(int j=0; j<Ntot; ++j)
			{
				if(connection[i][j]!=0)
				{
					tab_neuron[j].receive_spike(tab_neuron[i].getT_Clock(),g);
				}
			}
		}
	}
	
	
}	

 
int Network :: random(int start, int end)
{
	static random_device rd;
	static mt19937 gen(rd());
	static uniform_int_distribution<> connection_from(start,end-1);
	return connection_from(gen);
}

#include <iostream>
#include "neuron2.h"
#include <vector>
#include <cmath>
#include <fstream>
#include <random>
using namespace std;


Neuron :: Neuron () 
        {
			 V=0;
			 C=1; 
			 R=20;
			 Nb_Spikes_=0; 
			 Vext=2;
			 for (size_t i = 0; i< buffer.size(); ++i)
			 {
				 buffer[i] = 0;
			 }
			 
			 T_Clock=0;
			 
		}
		
				
int Neuron :: getT_Clock() const
{ 
	return T_Clock;
}

void Neuron :: incrementT_Clock( int t)	
{
	T_Clock= T_Clock+t;
}	

array<double,16> Neuron :: getbuffer() const
{
	 return buffer;
}	 
         
vector<double> Neuron :: getT() const
{ 				
	return T;
}

void Neuron :: setT(vector<double> t)			
{ 		
	T=t;	
}		

double Neuron :: getV() const
{ 
	return V;
}

int Neuron :: getNb_Spikes_() const
{ 
	return Nb_Spikes_;
}	
	
void Neuron :: setV(double v)
{
	V=v;
}	

void Neuron :: incrementNb_Spikes_()
{
	Nb_Spikes_=Nb_Spikes_ + 1; 
}		

bool Neuron :: spike(double Vth)
{
	if (V>Vth)
	{
		return true;
	}
	else return false;
}	
	
bool Neuron:: IsNeuron_refractory(double Vth, int simtime)
{
	if ((V>Vth) and ((simtime - T.back()) <= 2 ))
	{
		return true;
	}
	else return false;	
	
}

void Neuron :: fill_T(double t)
{
	T.push_back(t);
}	
	

bool Neuron :: update(double I,int arrival)
{
	T_Clock = arrival + D;
	if (spike(Vth))
	{
		incrementNb_Spikes_();
		fill_T(T_Clock);
		V=0.0;
		Spike=true;
	} 
	else 
	{
		Spike=false;
	}
	
	 if (IsNeuron_refractory(Vth, T_Clock))
	 {
		 V=0.0;
	 }
	 else
	 {  
	     int set_spike = ((T_Clock)%(D+1));
	     
	    // std::cout << "update " << set_spike << std::endl;
	
		 //static poisson_distribution<> poisson(2);  /*!< poisson */
		 //static random_device rd;	
		 //static mt19937 gen(rd());
		 
		 V_update=exp(-h/(R*C))*V + I*R*(1-exp(-h/(R*C))) + buffer[set_spike]; //+ poisson(gen)*0.1;/*!< updates the neuron state from time t to t+T ou T=n*h with n  the nbre of step */
		 V=V_update;
	
		 buffer[(T_Clock)%(D+1)]=0; /*!< put the case to 0 */
	 }	
	 ++T_Clock;
	 return Spike;
 }                                                                                                            

void Neuron :: receive_spike (double J) /*!< receive a spike at time arrival with J */
{	
	//std::cout << "receive " << (arrival)%(D+1) << std::endl;
	buffer[(T_Clock + D)%(D+1)]+=J; 
}	 

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

bool Neuron :: spike(double Vth) /*!< return trrue if the neuron spike */
{
	if (V>Vth)
	{
		return true;
	}
	else return false;
}	
	
bool Neuron:: IsNeuron_refractory(double Vth, int simtime) /*!< return true if a neuron is refractory, during refractory time (20 step) V=0 */
{
	if ((V=0) and ((simtime - T.back()) <= 20 ))
	{
		return true;
	}
	else return false;	
	
}

void Neuron :: fill_T(double t) /*!< fill the vector with the neuron's times of spikes */
{
	T.push_back(t);
}	
	

bool Neuron :: update(double I,int arrival)
{
	T_Clock = arrival + D;
	
	/**************************************************************************************************//**
     *  if the neuron spikes, we increment Nb_Spikes,
     * we initialize the bool Spike to true (this bool is what the fonction return) else, it is false
     * we store the time of the spike in the vector T of the neuron
     * we put the potential membran of the neuron at 0
     ****************************************************************************************************/
	
	if (spike(Vth))
	{
		++ Nb_Spikes_;
		fill_T(T_Clock);
		V=0.0;
		Spike=true;
	} 
	else 
	{
		Spike=false;
	}
	
	/**************************************************************************************************//**
     *  if the neuron has spiked, it is refractory
     * hisd potential membrane is 0 during 20 steps
     ****************************************************************************************************/
	
	if  ((!T.empty()) and ((T_Clock - T.back()) <= 20 ))
	 {
		 V=0.0;
	 }
	 
	 /**************************************************************************************************//**
     *  if the neuron didn't spike, we calculate the new value of the potentiel membran V 
     * we use poisson, the buffer and the current 
     ****************************************************************************************************/
	 
	 else
	 {  
	     int set_spike = ((T_Clock)%(D+1)); /*!< for the index of the tab where we have to look in the buffer */
	     
		 static poisson_distribution<> poisson(2);  /*!< poisson */
		 static random_device rd;	
		 static mt19937 gen(rd());
		 
		 V_update=exp(-h/(R*C))*V + I*R*(1-exp(-h/(R*C))) + buffer[set_spike] + poisson(gen)*0.1; /*!< updates the neuron state from time t to t+T ou T=n*h with n  the nbre of step */
		 V=V_update;
	
		 buffer[(T_Clock)%(D+1)]=0; /*!< put the case to 0 */
	 }	
	 ++T_Clock;
	 return Spike;
 }                                                                                                            

void Neuron :: receive_spike (double J) /*!< receive a spike at time arrival with J */
{	
	buffer[(T_Clock + D)%(D+1)]+=J; /*!< store the J in the good index of the buffer */
}	 

bool Neuron :: update_test(double I,int arrival)
{
	T_Clock = arrival + D;
	
	/**************************************************************************************************//**
     *  if the neuron spikes, we increment Nb_Spikes,
     * we initialize the bool Spike to true (this bool is what the fonction return) else, it is false
     * we store the time of the spike in the vector T of the neuron
     * we put the potential membran of the neuron at 0
     ****************************************************************************************************/
	
	if (spike(Vth))
	{
		++ Nb_Spikes_;
		fill_T(T_Clock);
		V=0.0;
		Spike=true;
	} 
	else 
	{
		Spike=false;
	}
	
	/**************************************************************************************************//**
     *  if the neuron has spiked, it is refractory
     * hisd potential membrane is 0 during 20 steps
     ****************************************************************************************************/
	
	if  ((!T.empty()) and ((T_Clock - T.back()) <= 20 ))
	 {
		 V=0.0;
	 }
	 
	 /**************************************************************************************************//**
     *  if the neuron didn't spike, we calculate the new value of the potentiel membran V 
     * we use poisson, the buffer and the current 
     ****************************************************************************************************/
	 
	 else
	 {  
	     int set_spike = ((T_Clock)%(D+1)); /*!< for the index of the tab where we have to look in the buffer */
	     
		 V_update=exp(-h/(R*C))*V + I*R*(1-exp(-h/(R*C))) + buffer[set_spike]; /*!< updates the neuron state from time t to t+T ou T=n*h with n  the nbre of step */
		 V=V_update;
	
		 buffer[(T_Clock)%(D+1)]=0; /*!< put the case to 0 */
	 }	
	 ++T_Clock;
	 return Spike;
 }                            

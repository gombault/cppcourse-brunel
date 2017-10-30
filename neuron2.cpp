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
			 Vext=0;
			 for (size_t i = 0; i< buffer.size(); ++i)
			 {
				 buffer[i] = 0;
			 }
			 
			 T_Clock=0;
			 
		}
		
int Neuron :: getD() const
{ 
	return D;
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
	
double Neuron :: getC() const
{ 
	return C;	
}

void Neuron :: setV(double v)
{
	V=v;
}	

void Neuron :: incrementNb_Spikes_()
{
	Nb_Spikes_=Nb_Spikes_ + 1; 
}		

void Neuron :: setC(double c)
{
	C=c;
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
	if ((V>Vth) and ((simtime-T.back()) <= 2 ))
	{
		return true;
	}
	else return false;	
	
}

void Neuron :: fill_T(double t)
{
	T.push_back(t);
}	
	

bool Neuron :: update(double I,double J,int arrival)
{
	int Vth=20;
	double h=0.1;
	double V_update;
	bool Spike = false;
	
	if (spike(Vth))
	{
		incrementNb_Spikes_();
		fill_T(T_Clock);
		Spike=true;
	} 
	 if (IsNeuron_refractory(Vth,T_Clock))
	 {
		 V=0.0;
	 }
	 else
	 {  
		 receive_spike(T_Clock, J);
	     int set_spike = ((arrival+D+1)%(D+1));
	
	     //std::cout << "update " << set_spike << std::endl;
		 static poisson_distribution<> poisson(Vext*0.1*10000*h*0.1); // poisson
		 static random_device rd;	
		 static mt19937 gen(rd());
		 
		 V_update=exp(-h/(R*C))*V + I*R*(1-exp(-h/(R*C))) + buffer[set_spike] + poisson(gen);// updates the neuron state from time t to t+T ou T=n*h with n  the nbre of step
		 V=V_update;
		 buffer[(arrival)%(D+1)]=0; // remettre la case du tableau a 0
	 }	
	 return Spike;
 }                                                                                                            
	
/*void Neuron :: update_connection(double J,int arrival) // update the neuron from time t=tclock to t=tclock+steps-1 the neuron passes from V=10 to V=10+J
{
	receive_spike(T_Clock, J);
	int set_spike = ((arrival+D+1)%(D+1));
	
	std::cout << "update " << set_spike << std::endl;
	V += buffer[set_spike]; // V takes the value of what contain the vector at the indice 
    buffer[(arrival)%(D+1)]=0; // remettre la case du tableau a 0
}*/ 

void Neuron :: receive_spike(int arrival, double J) // receive a spike at time arrival with J
{	
	//std::cout << "receive " << (arrival)%(D+1) << std::endl;
	
	buffer[(arrival)%(D+1)]+=J; 
}	 

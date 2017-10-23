#include <iostream>
#include "neuron2.h"
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;


Neuron :: Neuron () 
        {
			 V=10;
			 C=1; 
			 R=20;
			 Nb_Spikes_=0; 
			 //int n=50;//nbre de steps
			 //int h=1; // temps d'un step
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

void Neuron :: setT_Clock( int t)	
{
	T_Clock= T_Clock+t;
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

void Neuron :: setNb_Spikes_()
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
	

void Neuron :: update(double I)
{
	int Vth=20;
	int h=1;
	double V_update;
	
	if (spike(Vth))
	{
		fill_T(T_Clock);
	} 
	 if (IsNeuron_refractory(Vth,T_Clock))
	 {
		 V=10;
	 }
	 else
	 {  	
		 V_update=exp(-h/(R*C))*V + I*R*(1-exp(-h/(R*C)));// updates the neuron state from time t to t+T ou T=n*h qvec n nbre de step
		 V=V_update;
	 }	
 }                                                                                                            
	
void Neuron :: update_connection(double I, double J, double arrival) // update l'etat du neuron du temps t=tclock to t=tclock+steps-1 le neuron passe de V=10 a V=10+J
{
	int h=1;
	receive_spike(T_Clock, J);

		  int nb_step = arrival/h;
	      V += buffer[(nb_step%(D+1))]; // V+= a ce au'il y a ds la case du tableau, 0, J ou 2J...
	      buffer[(nb_step+D)%(D+1)]=0; // remettre la case du tableau a 0
} 

void Neuron :: receive_spike(double arrival, double J) // recoit un spike au temps arrival avec J, si plus d'un spike arrive en meme temps on additione les indices  arrival = 
{
	int h(1);
	int nb_step = arrival/h;
	buffer[(nb_step+D)%(D+1)]+=J; 
}	 

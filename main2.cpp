#include <iostream>
#include "neuron2.h"
#include <fstream>
using namespace std;

int main()
{
	
double T_start(0); // time where the simulation starts
double T_stop(5000); // time where the simulation ends
int n(50); // number of  step
double h(0.1); // time of a step
int simtime(n*h); // simulation time
double Vth(20); // potentiel value where the neuron spike
double input_current(0); // value of current
double J(0.1);


ofstream fichier("potentielmembrane.txt", ios::out | ios::app); 
fichier.clear();

cout << "entrer la valeure du courant:" ;
double I;
cin >> I;

cout << "entrer le temps minimum a ";
double a;
cin >> a;
cout <<"entrer le temps maximum b ";
double b;
cin >> b;

simtime=T_start;

Neuron neuron1;
Neuron neuron2;


while(simtime < T_stop)
{
	if ((a<=simtime) and (b>=simtime)) // there is current between time a and b
	{
		input_current=I;
	}
	else // else current is 0
	{
		input_current=0;
	}
	if ((!neuron1.getT().empty()) and (neuron1.getT().back() <= simtime) and (simtime <= (neuron1.getT().back()+1))) // during the refraction periode, the value of the potential membrane of the neuron1 is 0
	{
		neuron1.setV(0);
	}
	else if (neuron1.getV()>Vth) // if neuron1 spike, his potential membran go back to 0 and neuron2 shows a respond with a delay of 15ms
	{
		neuron1.update(input_current);
		//neuron1.incrementNb_Spikes_();
	    fichier << " il y a eu " << neuron1.getNb_Spikes_() <<" spikes " << endl;
		neuron1.setV(0);
		neuron2.update_connection(J,neuron1.getT().back());
		fichier<< "la valeur du potentiel de la membrane du neuron 2 au temps :" << simtime << "ms vaut :" << neuron2.getV() << endl; 
		
		
			
    }
	else // else, neuron 1 is update at every step with a current of I, same with neuron2 with a current of 0 untill neuron2 potentiel value go back to 0
	{
		neuron1.update(input_current);
		neuron2.update(0);
	}	
	
		
	simtime +=h;
	neuron1.incrementT_Clock(h);// at every step, local time of neuron 1 and 2 are incremented
	neuron2.incrementT_Clock(h);
	fichier << "la valeur du potentiel de la membrane du neuron 1 au temps :" << simtime << "ms, vaut: " << neuron1.getV() << " et celle du neuron 2 vaut :" << neuron2.getV() << endl;
	

}
fichier.close();
}	
	



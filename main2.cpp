#include <iostream>
#include "neuron2.h"
#include <fstream>
using namespace std;

int main()
{
	
double T_start(0); //time where the simulation starts 
double T_stop(5000); // time where the simulation ends 
double simtime(0); // simulation time 
double Vth(20); // potentiel value where the neuron spike 
double input_current(0); // value of current 
double J(0.1); // current passed to other neurons when spike 

/*******************************************************************************************
     *    creation of a fold where we can write the membran potential value
     ****************************************************************************************/

ofstream fichier("potentielmembrane2.txt", ios::out | ios::app); 
fichier.clear();

/*******************************************************************************************
     *    we ask the input current to the users 
     *    we also ask at what time the user want to put current vand when he wants to stop it
     ****************************************************************************************/

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

/*******************************************************************************************
     *    simulation loop
     ****************************************************************************************/



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

	 if (neuron1.getV() > Vth) // if neuron1 spike, his potential membran go back to 0 and neuron2 shows a respond with a delay of 1,5ms 
	{
		neuron1.update_test(input_current);
		neuron2.receive_spike(J, simtime);
	    fichier << " il y a eu " << neuron1.getNb_Spikes_() <<" spikes " << endl;
	}
	else // else, neuron 1 is update at every step with a current of I, same with neuron2 with a current of 0 untill neuron2 potentiel value go back to 0 
	{
		neuron1.update_test(input_current);
		neuron2.update_test(1);
	}	
	
		
	++simtime; // we increment T_Clock at every step 
	fichier << "la valeur du potentiel de la membrane du neuron 1 au temps :" << simtime*0.1 << "ms, vaut: " << neuron1.getV() << " et celle du neuron 2 vaut :" << neuron2.getV() << endl;
	

}

fichier.close();

}	
	



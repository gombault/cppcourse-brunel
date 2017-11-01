#include <iostream>
#include "neuron2.h"
#include <fstream>
using namespace std;

int main()
{
	
double T_start(0); /*!< time where the simulation starts */
double T_stop(1000); /*!< time where the simulation ends */
double simtime(0);
double Vth(20); /*!< potentiel value where the neuron spike */
double input_current(0); /*!< value of current */
double J(0.1); /*!< current passed to other neurons when spike */

/*****************************************************************************************//**
     *    creation of a fold where we can write the membran potential value
     ****************************************************************************************/

ofstream fichier("potentielmembrane.txt", ios::out | ios::app); 
fichier.clear();

/*****************************************************************************************//**
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

/*****************************************************************************************//**
     *    simulation loop
     ****************************************************************************************/



while(simtime < T_stop)
{
	if ((a<=simtime) and (b>=simtime)) /*!< there is current between time a and b */
	{
		input_current=I;
	}
	else /*!< else current is 0 */
	{
		input_current=0;
	}
	if ((!neuron1.getT().empty()) and (neuron1.getT().back() <= simtime) and (simtime <= (neuron1.getT().back()+1))) /*!< during the refraction periode, the value of the potential membrane of the neuron1 is 0 */
	{
		neuron1.setV(0);
	}
	else if (neuron1.getV() > Vth) /*!< if neuron1 spike, his potential membran go back to 0 and neuron2 shows a respond with a delay of 15ms */
	{
		neuron2.receive_spike(J);
		neuron1.update(input_current,0);
		//neuron1.incrementNb_Spikes_();
	    fichier << " il y a eu " << neuron1.getNb_Spikes_() <<" spikes " << endl;
		neuron1.setV(0);
		neuron2.update(0,neuron1.getT().back());
		fichier<< "la valeur du potentiel de la membrane du neuron 2 au temps :" << simtime << "ms vaut :" << neuron2.getV() << endl; 
		
		
			
    }
	else /*!< else, neuron 1 is update at every step with a current of I, same with neuron2 with a current of 0 untill neuron2 potentiel value go back to 0 */
	{
		neuron1.update(input_current,simtime);
		neuron2.update(0,simtime);
	}	
	
		
	++simtime;
	neuron1.incrementT_Clock(1);/*!< at every step, local time of neuron 1 and 2 are incremented */
	neuron2.incrementT_Clock(1);
	fichier << "la valeur du potentiel de la membrane du neuron 1 au temps :" << simtime << "ms, vaut: " << neuron1.getV() << " et celle du neuron 2 vaut :" << neuron2.getV() << endl;
	

}
fichier.close();
}	
	



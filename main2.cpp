#include <iostream>
#include "neuron2.h"
#include <fstream>
using namespace std;

int main()
{
	
double T_start(0); // temps du début de simulation
double T_stop(180); // temps de fin de simulatio
int n(50); // nombre de step
int h(1); // temps d'un step
int simtime(n*h); // temps de simulation
double Vth(20); // valeur du potentiel ou un spike a lieu
double input_current(0); // courant 
double J(0.1);


ofstream fichier("potentielmembrane.txt", ios::out | ios::app);

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
	if ((a<=simtime) and (b>=simtime))
	{
		input_current=I;
	}
	else 
	{
		input_current=0;
	}
	if ((!neuron1.getT().empty()) and (neuron1.getT().back() <= simtime) and (simtime <= (neuron1.getT().back()+2)))
	{
		neuron1.setV(10);
	}
	else if (neuron1.getV()>Vth)
	{
		neuron1.update(input_current);
		neuron1.setNb_Spikes_();
	    fichier << " il y a eu " << neuron1.getNb_Spikes_() <<" spikes " << endl;
		neuron1.setV(10);
		neuron2.update_connection(0,J,neuron1.getT().back());
		fichier<< "la valeur du potentiel de la membrane du neuron 2 au temps :" << simtime << "ms vaut :" << neuron2.getV() << endl; 
		fichier<< "T_Clock1 = " << neuron1.getT_Clock() << " et T_Clock2 = " << neuron2.getT_Clock() << endl;
			
    }
	else
	{
		neuron1.update(input_current);
	}	
	if((!neuron1.getT().empty()) and (neuron1.getT().back() <= simtime) and (simtime <= (neuron1.getT().back()+10)))
		{
			neuron2.update(0);
		}
		
	simtime +=h;
	neuron1.setT_Clock(h);
	neuron2.setT_Clock(h);
	fichier << "la valeur du potentiel de la membrane du neuron 1 au temps :" << simtime << "ms, vaut: " << neuron1.getV() << " et celle du neuron 2 vaut :" << neuron2.getV() << endl;
	

}
fichier.close();
}	
	



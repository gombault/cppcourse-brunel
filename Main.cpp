#include <iostream>
#include "neurone.h"
#include <fstream>
using namespace std;

int main()
{
	
double T_start(0);
double T_stop(200);
double n(50);
double h(1);
double simtime(n*h);
double Vth(20);
double input_current(0);

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

while(simtime < T_stop)
{
	if ((a<=simtime) and (b>=simtime))
	{
		input_current=I;
	}
	else input_current=0;
	if ((!neuron1.getT().empty()) and (neuron1.getT().back() <= simtime) and (simtime <= (neuron1.getT().back()+2)))
	{
		neuron1.setV(10);
	}
	else if (neuron1.getV()>Vth)
	{
		neuron1.fill_T(simtime);
		neuron1.update(input_current);
		neuron1.setNb_Spikes_();
	    fichier << " il y a eu " << neuron1.getNb_Spikes_() <<" spikes " << endl;
		neuron1.setV(10);
		
    }
	else
	{
		neuron1.update(input_current);
	}	
	
	simtime +=h;
	fichier << "la valeur du potentiel de la membrane au temps :" << simtime << "ms, V=" << neuron1.getV() << endl;

}
fichier.close();
}	
	



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


ofstream fichier("potentielmembrane.txt", ios::out |ios::app);

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

Neuron neuron;

while(simtime < T_stop)
{
	if ((a<=simtime) and (b>=simtime))
	{
		input_current=I;
	}
	else input_current=0;
	if ((!neuron.getT().empty()) and (neuron.getT().back() <= simtime) and (simtime <= (neuron.getT().back()+2)))
	{
		neuron.setV(10);
		fichier<< "la valeur du potentiel de la membrane lors de la periode de refraction vaut: " << neuron.getV() << endl;
	}
	else if (neuron.getV()>Vth)
	{
		neuron.fill_T(simtime);
		neuron.update(input_current);
		fichier<< " spike " << endl;
		neuron.setV(10);
		/*while(simtime <= simtime +10) // faire en sorte que le potentiel de la membrane reste a 10 pendant le refractory time 
		{
		neuron.setV(10);
		}*/
		
    }
	else
	{
		neuron.update(input_current);
	}	
	
	simtime +=h;
	fichier << "la veleur du potentiel de la membrane au temps :" << simtime << "ms, V=" << neuron.getV() << endl;

}
fichier << " il y a eu " << neuron.getNb_Spikes_() << endl;
fichier.close();
}	
	



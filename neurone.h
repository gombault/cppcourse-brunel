#include <iostream>
#include <vector>
using namespace std;


class Neuron
{ 
	
private:

double V; //potentiel de la membrane 

int Nb_Spikes_;

vector<double> T; // temps ou le pic a lieu

double C; // conductance du neuron

double R; // resistance 


public:

Neuron ();

double getV() const;

vector<double> getT() const;

vector<double> setT(vector<double> t);

int getNb_Spikes_() const;

double getC() const;

void setC(double c);

void setV(double v);

void setNb_Spikes_(int s);

void update(double I); //change l'etat du neurone, du temps t au temps t+T ou T=n*h

bool IsNeuron_refractory(double Vth); // nous dit si le neuron est refracte 

void fill_T(double t);	
	
};

#include <iostream>
#include <vector>
#include <array>
using namespace std;


class Neuron
{ 
	
private:

double V; //potentiel de la membrane 

int Nb_Spikes_;

vector<double> T; // temps ou le pic a lieu = temps de refraction (2ms)

double C; // conductance du neuron

double R; // resistance 

int T_Clock; // temps propre au neuron

static const int D=15 ; // delay

array<int,(D+1)> buffer; // tableau qui store les J recu au differents t_spike +D


public:

Neuron ();

int getD() const;

int getT_Clock() const;

void setT_Clock( int t);

double getV() const;

vector<double> getT() const;

void setT(vector<double> t);

int getNb_Spikes_() const;

double getC() const;

void setC(double c);

void setV(double v);

void setNb_Spikes_();

void update(double I); //change l'etat du neurone, du temps t au temps t+T ou T=n*h

bool IsNeuron_refractory(double Vth, int simtime); // nous dit si le neuron est refracte 

void fill_T(double t);

bool spike(double vth);

void update_connection(double I, double J, double arrival); // update l'etat du neuron du temps t=tclock to t=tclock+steps-1

void receive_spike(double arrival, double J); // recoit un spike au temps arrival avec J, si plus d'un spike arrive en meme temps on additione les indices 
	
};

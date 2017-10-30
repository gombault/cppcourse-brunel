#include <iostream>
#include <vector>
#include <array>
using namespace std;


class Neuron
{ 
	
private:

double V; //membran potential

int Nb_Spikes_;

vector<double> T; // refraction time (2ms)

double C; // conductance 

double R; // resistance 

int T_Clock; // local time

static const int D=15 ; // delay

array<double,(D+1)> buffer; //  store the J receive at the different t_spike +D

double Vext;

double W; //w=g pour neuron inhibitor et c=J pour neuron excitator


public:

Neuron ();

// getters and setters

int getD() const;

int getT_Clock() const;

double getV() const;

vector<double> getT() const;

void setT(vector<double> t);

int getNb_Spikes_() const;

double getC() const;

void setC(double c);

void setV(double v);

array<double,16> getbuffer() const;

//functions

void incrementNb_Spikes_();

void incrementT_Clock( int t);

bool update(double I,double J, int arrival); // update the neuron from time t to t+T where T=n*h

bool IsNeuron_refractory(double Vth, int simtime); 

void fill_T(double t);

bool spike(double vth);

void update_connection(double J,int arrival); // update the neuron from time t=tclock to t=tclock+steps-1

void receive_spike(int arrival, double J); // receive a spike at time arrival with J, if more than a spike arrive at the same time we sum the indices 
	
};

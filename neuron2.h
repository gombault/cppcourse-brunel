#include <iostream>
#include <vector>
#include <array>
using namespace std;


class Neuron
{ 
	
private:

double V; /*!< membran potential */

int Nb_Spikes_;

vector<double> T; /*!< vector of spike times */

double C; /*!< conductance */

double R; /*!< resistance */

int T_Clock; /*!< local time */

static const int D=15 ; /*!<delay */

array<double,(D+1)> buffer; /*!< store the J receive at the different t_spike +D */

double Vext;

int Vth=20;
double h=0.1;
double V_update;
bool Spike = false;


public:

Neuron ();

/**************************************************************//**
     *    getters and setters
     ******************************************************************/


int getT_Clock() const;

double getV() const;

vector<double> getT() const;

void setT(vector<double> t);

int getNb_Spikes_() const;

void setV(double v);

array<double,16> getbuffer() const;

/**************************************************************//**
     *    functions
     ******************************************************************/

bool update(double I, int arrival); /*!< update the neuron from time t to t+T where T=n*h */

bool IsNeuron_refractory(double Vth, int simtime); /*!< return true if have spiked and set his membran potentiel to 0 during 2ms */

void fill_T(double t); /*!< fill the vector with the differents times where the neuron have spiked */

bool spike(double vth); /*!< says if the neuron spike or not */

void update_connection(double J,int arrival); /*!< update the neuron from time t=tclock to t=tclock+steps-1  */

void receive_spike( double J); /*!< receive a spike at time arrival with J, if more than a spike arrive at the same time we sum the indices */
	
};

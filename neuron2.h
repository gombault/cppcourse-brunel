#include <iostream>
#include <vector>
#include <array>
using namespace std;


class Neuron
{ 
	
private:

/***************************************************************//****
     *   attributs
     ******************************************************************/

double V; //! membran potential 

int Nb_Spikes_; //! number spikes

vector<double> T; //! vector of spike times 

double C; //! conductance 

double R; //! resistance 

int T_Clock; //! local time 

static const int D=15 ; //!delay 

array<double,(D+1)> buffer; //! store the J receive at the different t_spike +D 

double Vext;

/**************************************************************//**
     *    constants 
     ******************************************************************/

int Vth=20;
double h=0.1;
double V_update;
bool Spike = false;


public:

Neuron ();

/**************************************************************//**
     *    getters and setters
     ******************************************************************/
/**
 * @return T_Clock the internal time of the neuron
 */
int getT_Clock() const;

/**
 * @return V the potentiel membran of the neuron
 */
double getV() const;

/**
 * @return T the vector of spikes time of the neuron
 */
vector<double> getT() const;

/**
 * @param t an argument to fill T
 */
void setT(vector<double> t);

/**
 * @return Nb_Spikes the number of spike of the neuron
 */
int getNb_Spikes_() const;

/**
 * @param v an argument to initialize the potentiel membran 
 */
void setV(double v);

/**************************************************************//**
     *    functions
     ******************************************************************/
/**
 * @brief update the neuron from time t to t+T where T=n*h with poisson
 * @param I the input current
 * @param arrival the time when we call update
 * @return if it spike or not
 */
bool update(double I, int arrival); 

/**
 * @brief return true if have spiked and set his membran potentiel to 0 during 2ms
 * @param Vth the treeshold value which is 20
 * @param simtime the simulation time
 * @return if it is refractory or not 
 */
bool IsNeuron_refractory(double Vth, int simtime); 

/**
 * @brief fill the vector with the differents times where the neuron have spiked
 * @param t the time when the neuron have spiked
 */
void fill_T(double t); 

/**
 * @brief says if the neuron spike or not
 * @param Vth the treeshold value which is 20
 * @return if it spike or not
 */
bool spike(double vth);
 
/**
 * @brief receive a spike at time arrival with J, if more than a spike arrive at the same time we sum the indices
 * @param J the current send by the neuron which have spiked
 */
void receive_spike(double J);

/**
 * @brief update the neuron from time t to t+T where T=n*h without poisson
 * @param I the input current
 * @param arrival the time when we call update
 * @return if it spike or not
 */
bool update_test(double I,int arrival);
	
};

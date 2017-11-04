#include <iostream>
#include <vector>
#include <array>
#include "neuron2.h"
using namespace std;

class Network
{
	private:
	
	int Ntot; //!< number of neurons 
	int Ne; //!< number of excitatory neurons 
	int Ni; //!< Number of inhibithory neurons 
	int Ci; //!< Number of inhibitory connections 
	int Ce; //!< Number of excitatory connections
	double Je; //!< currant of excitatory neuron 
	double Ji; //!< currant of inhibitory neuron
	int Cext; //!<connections from the rest of the brain, this is randomly generated spikes cf Poisson 
	vector<vector<double>> connection; //!< connections tab 
	vector<Neuron>tab_neuron; //!< neurons tab
	
	public:
	
/**
 * @brief constructor
 */
	Network(); 
	
/**
 * @brief fonction that fill the connections tab using random
 */	
	void fill_connection(); 
	
/**
 * @brief update the neuron from time t to t+T where T=n*h
 * @param time the simulation time
 */	
	void update(int time);
};

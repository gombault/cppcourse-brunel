#include <iostream>
#include <vector>
#include <array>
#include "neuron2.h"
using namespace std;

class Network
{
	private:
	
	int Ntot; /*!< number of neurons */
	int Ne; /*!< number of excitatory neurons */
	int Ni; /*!< Number of inhibithory neurons */
	int Ci; /*!< Number of inhibitory connections */
	int Ce; /*!< Number of excitatory connections*/
	double Je; /*!< currant of excitatory neuron */
	double Ji; /*!< currant of inhibitory neuron*/
	int Cext; /*!< connections from the rest of the brain, this is randomly generated spikes cf Poisson */
	vector<vector<double>> connection; /*!< connections tab */
	vector<Neuron>tab_neuron; /*!< neurons tab*/
	
	public:
	
/**
 * constructor
 */
	Network(); 
	
/**
 * fonction that fill the connections tab using random
 */	
	void fill_connection(); 
	
/**
 * fonction that chose randomly number in a interval to fill the connections tab
 * @param start an argument to define the beginning of my interval
 * @param end an argument to define the end of my interval 
 * @return the number chosen in the interval
 */			
	int random(int start,int end); 
	
/**
 * update the neuron from time t to t+T where T=n*h
 * @param time the simulation time
 */	
	void update(int time);
};

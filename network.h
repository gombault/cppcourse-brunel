#include <iostream>
#include <vector>
#include <array>
#include "neuron2.h"
using namespace std;

class Network
{
	private:
	
	int Ntot;
	int Ne; //number of excitatory neurons 
	int Ni; // Number of inhibithory neurons
	int Ci; // Number of inhibitory connections
	int Ce; // Number of excitatory connections
	double Je; // currant of excitatory neuron
	double Ji; // currant of inhibitory neuron
	int Cext; // connections from the rest of the brain, this is randomly generated spikes cf Poisson
	vector<vector<double>> connection;
	vector<Neuron> tab_neuron;
	double g;
	double J;
	
	public:
	
	Network();
	void fill_connection();
	int random(int start,int end);
	void update();
};

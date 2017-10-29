#include <iostream>
#include <vector>
#include <array>
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
	int g; // g=Ji/Je
	int Cext; // connections from the rest of the brain, this is randomly generated spikes cf Poisson
	array<array<int,12500>,12500> connection; 
	
	public:
	
	Network();
	void fill_connection();
	int random(int N1,int N2);
};

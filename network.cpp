#include <iostream>
#include "network.h"
#include <vector>
#include <cmath>
#include <fstream>
#include <random>
using namespace std;



Network :: Network () 
        {
			Ntot=12500;
		    Ne=10000;
			Ni=2500;
			Ce=1000;
			Ci=250;
			Je=0.1;
			Ji=0.5;
			g=5;
			 for (size_t i=0; i< 25000; ++i)
			 {
				 for(size_t j=0; j<25000; ++j)
				 connection[i][j] = 0;
			 }
		}
		
void Network :: fill_connection()
 {
	 for(int i=0; i<12500; ++i) // on itere le long du tableau verticalement
	 {
		 for(int j=0; j<0.1*Ne; ++j) // on itere le long du tableau horizontalement d'abbord sur les 10000 premieres cases pour les 10000 excitatory neurons
		 {
			  connection[random(0,Ne)][i]+=1;
		  }
		  for(int h=0; h<0.1*Ni; ++h) // puis on itere sur les 2500 dernieres cases pour les neurons inhibiteurs
		  {
			 connection[random(Ne,Ntot)][i]+=1;
		  }
	 }
 }
	 
int Network :: random(int start, int end)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> connection_from(start,end-1);
	return connection_from(gen);
}

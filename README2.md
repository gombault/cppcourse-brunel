# cppcourse-brunel
Spiking network simulation discribe in " Brunel  NJ.Comp Neuroscience 2000"
My program simulate the activity of a neural network composed of 12500 neurons of which 10000 are excitators and 2500 inhibitors with 
connections generated randomly.

After downloading my github depository , you have to download google test on github and put it in the folder.

To compile my program, you need to make the following commands on the terminal:
1)Change directory to the "build" folder 
2)Enter make
3)then enter ./neuron

This will create a file named "Spike.gdf" in which the number of the spiking neuron is written and the time when it spiked.
You will use this file to product the Brunel figures on Python.

There are 4 figures to product:

      figure a): 1)initialize Ji at -0.3 in the Network constructor in the file network.cpp
                 2)Poisson take 2 in parameter in the file neuron2.cpp in the function update().
                 3)run the program from simtime=0 and T_stop=6000.
                 4) change the if condition to write in the file the time and spiking neuron between 5000 and 6000.
                 This figure should show a pattern on Python.
                 
      figure b): 1)initialize Ji at -0.6 in the Network constructor in the file network.cpp
                 2)Poisson take 4 in parameter in the file neuron2.cpp in the function update().
                 3)run the program from simtime=0 and T_stop=12000.
                 4) change the if condition to write in the file the time and spiking neuron between 10000 and 12000.
                 
      figure c): 1)initialize Ji at -0.5 in the Network constructor in the file network.cpp
                 2)Poisson take 2 in parameter in the file neuron2.cpp in the function update().
                 3)run the program from simtime=0 and T_stop=12000.
                 4) change the if condition to write in the file the time and spiking neuron between 10000 and 12000.
                 
      figure d): 1)initialize Ji at -0.45 in the Network constructor in the file network.cpp
                 2)Poisson take 0.9 in parameter in the file neuron2.cpp in the function update().
                 3)run the program from simtime=0 and T_stop=12000.
                 4) change the if condition to write in the file the time and spiking neuron between 10000 and 12000.
                 
                 
To compile the google tests ( test to show how interact 1 and 2 neurons); write the following commands on the terminal:
1)Change directory to the "build" folder 
2)Enter make
3)then enter ./neuron_unittest

To check the behavior of one single neuron or two, make the following commands on the terminal:
1)g++ -c neuron2.cpp main2.cpp 
2)g++ neuron2.o main2.o -o test
3)./test
This will generate a file called "PotentialMembran.txt" in which you can see the the value of the potential membran of the neuron at every step
and when the neuron spikes.

To generate the doxygen file:
make the following commands in the terminal:
1) doxygen Doxyfile.In
2)cd build
3) make doc 
Then you go in the folder Html and click on the file annotated.html which will open a window in the internet where you could see the commants
on my code.



                 
                 
                 
                 
        
      

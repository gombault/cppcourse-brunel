#include "neuron2.h"
#include "gtest/gtest.h"
#include <iostream>
#include <cmath>


TEST (NeuronTest, PositiveInput) // check the value of the potential membrane for differemt input current 
{
	Neuron neuron;
	double I (1.0);
	// first update test
	neuron.update(I,0);
	EXPECT_EQ(20.0*(1.0-std::exp(-0.1/20.0)), neuron.getV());
	neuron.setV(0);
	
	// test after numerous updates
	for (int i(0); i<10000; ++i)
	{
		neuron.update(I,0);
	}
	// the membrane potential should tend to 20 but never reach v=20
	// so the neuron should never spike
	EXPECT_EQ(0, neuron.getNb_Spikes_());
	EXPECT_GT(1E-3, std::fabs(19.999 - neuron.getV()));
	neuron.setV(0);
	
	//the membrane potential should tend towards 0 with I=0
	I=0;
	for(int i(0); i<2000; ++i)
	{
		neuron.update(I,0);
	}
	EXPECT_NEAR(0, neuron.getV(), 1e-3);
	neuron.setV(0);
}



int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}

TEST(NeuronTest, NegativeInput) 
{
	Neuron neuron;
	double I=-1.00;
	// first update test
	neuron.update(I,0);
	EXPECT_EQ(-20.0*(1.0-std::exp(-0.1/20.0)), neuron.getV());
	neuron.setV(0);
	
	//test after numerous updates
	for(int i(0); i<10000; ++i)
	{
		neuron.update(I,i);
	}
	// The membran potential should tend to -20
	EXPECT_GT(1E-3, std::fabs(-19.999 -neuron.getV()));
	neuron.setV(0);
	
	
	// The membran potential should tend naturally toward 0 with I=0
	I=0;
	for(int i(0); i<2000; ++i)
	{
		neuron.update(I,i);
	}
	EXPECT_NEAR(0, neuron.getV(), 1e-3);
}

TEST (NeuronTest, SpikeTimes)
{
	Neuron neuron;
	double I=1.01;
	// we know that the spike times are at 92.4 ms, 186.9 ms, 281.4 ms and 375.6ms
	//waiting for the first spike 
	//we also check that the value of the potential membran go back to 0 after the spike
	for(int i(0); i<924; ++i)
	{
		neuron.update(I,i);
	}
	EXPECT_EQ(0, neuron.getNb_Spikes_());
	neuron.update(I,1);
	EXPECT_EQ(1, neuron.getNb_Spikes_());
	EXPECT_EQ(0.0, neuron.getV());
	
    //waiting for the second spike
    neuron.setV(0); 
    for(int i(0); i<1869; ++i)
    {
		neuron.update(I,i);
	}
	neuron.update(I,1869);
	EXPECT_EQ(2,neuron.getNb_Spikes_());
}
		
TEST(NeuronTest, StandaloneSimulation) // check the number of occuring spikes during the simulation of a neuron
{
	Neuron neuron;
	double I=1.01;
	// we know that the spike times are at 92.4 ms, 186.8 ms, 281.2 ms and 375.6ms
	// we are waiting for 3 spikes 
	for( int i(0); i<4000; ++i)
	{
		neuron.update(I,i);
	}
	EXPECT_EQ(4, neuron.getNb_Spikes_());
}

TEST(TwoNeurons, NoPSSpike) 
{
	Neuron neuron1, neuron2;
	int delay = 15;
	double I=1.01;
	//we wait for the first spike and see the impact on the other neuron2
	for(auto i=0; i<925+delay; ++i)
	{
		neuron1.update(I,i);
		if(neuron1.spike(20))
		{
			neuron1.update(I,1);
			neuron2.receive_spike(0.1);
			EXPECT_EQ(0.0, neuron1.getV());
		}	
		neuron2.update(0,i);
	}
	EXPECT_NEAR(0.1, neuron2.getV(),1e-3);
}

TEST(TwoNeurons, WithPSSpike) // a revoir
{
	Neuron neuron1, neuron2;
	int delay = 15;
	double I1=1.01;
	double I2=1.0;
	// we wait for the second spike of neuron 1 to see neuron 2 spike because neuron1 did not have time to reach the treshold
	for(auto i=0; i<1870+delay; ++i)
	{
		neuron1.update(I1,i);
		if(neuron1.update(I1,i))
		{
			neuron2.receive_spike(0.1);
			EXPECT_EQ(0, neuron2.getV());	
		}
		neuron2.update(I2,1871);
	}
	EXPECT_EQ(0, neuron2.getNb_Spikes_());
	
	neuron2.update(I2,1872);
	
	EXPECT_EQ(0,neuron2.getV());
	EXPECT_EQ(1, neuron2.getNb_Spikes_());

}
	
	
	

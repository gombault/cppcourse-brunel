#include "neuron2.h"
#include "gtest/gtest.h"
#include <iostream>
#include <cmath>

/*****************************************************************************************************************************//**
     *  check the value of the potential membrane for differemt input current 
     * we check for the first step the value of the potential membran with an imput current of 1
     * then we check the value of V after several steps V should tend to 0 but never reach 0 so the neurom should not spike
     * for I=0, V should tends toward 0 
     ***************************************************************************************************************************/

TEST (NeuronTest, PositiveInput) 
{
	Neuron neuron;
	double I (1.0);
	
	// first update test
	neuron.update_test(I);
	EXPECT_EQ(20.0*(1.0-std::exp(-0.1/20.0)), neuron.getV());
	neuron.setV(0);
	
	// test after numerous updates
	for (int i(0); i<10000; ++i)
	{
		neuron.update_test(I);
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
		neuron.update_test(I);
	}
	EXPECT_NEAR(0, neuron.getV(), 1e-3);
	neuron.setV(0);
}


/*****************************************************************************************************************************//**
     *  check the value of the potential membrane for differemt input current 
     * we check for the first step the value of the potential membran with an imput current of 1
     * then we check the value of V after several steps V should tend to 0 but never reach 0 so the neurom should not spike
     * for I=0, V should tends toward 0 
     ***************************************************************************************************************************/

TEST(NeuronTest, NegativeInput) 
{
	Neuron neuron;
	double I=-1.00;
	// first update test
	neuron.update_test(I);
	EXPECT_EQ(-20.0*(1.0-std::exp(-0.1/20.0)), neuron.getV());
	neuron.setV(0);
	
	//test after numerous updates
	for(int i(0); i<10000; ++i)
	{
		neuron.update_test(I);
	}
	// The membran potential should tend to -20
	EXPECT_GT(1E-3, std::fabs(-19.999 -neuron.getV()));
	neuron.setV(0);
	
	
	// The membran potential should tend naturally toward 0 with I=0
	I=0;
	for(int i(0); i<2000; ++i)
	{
		neuron.update_test(I);
	}
	EXPECT_NEAR(0, neuron.getV(), 1e-3);
}

/*****************************************************************************************************************************//**
     *	we know that the spike times are at 92.4 ms, 186.9 ms, 281.4 ms and 375.6ms
     * we wait for the first spike and check the number of spike of the neuron, it should be one
     * we also check that the value of the potential membran go back to 0 after the spike
     * Then we wait for the second spike and check the number of spike which should be 2
     ***************************************************************************************************************************/

TEST (NeuronTest, SpikeTimes)
{
	Neuron neuron;
	double I=1.01;
	//waiting for the first spike 
	for(int i(0); i<924; ++i)
	{
		neuron.update_test(I);
	}
	EXPECT_EQ(0, neuron.getNb_Spikes_());
	neuron.update_test(I);
	EXPECT_EQ(1, neuron.getNb_Spikes_());
	EXPECT_EQ(0.0, neuron.getV());
	
    //waiting for the second spike
    neuron.setV(0); 
    for(int i(0); i<1869; ++i)
    {
		neuron.update_test(I);
	}
	neuron.update_test(I);
	EXPECT_EQ(2,neuron.getNb_Spikes_());
}

	/*****************************************************************************************************************************//**
     * check the number of occuring spikes during the simulation of a neuron
     * we know that the spike times are at 92.4 ms, 186.8 ms, 281.2 ms and 375.6ms
     * we are waiting for 4 spikes and check the number of spike
     ***************************************************************************************************************************/
			
TEST(NeuronTest, StandaloneSimulation) 
{
	Neuron neuron;
	double I=1.01;
	// we know that the spike times are at 92.4 ms, 186.8 ms, 281.2 ms and 375.6ms
	// we are waiting for 3 spikes 
	for( int i(0); i<4000; ++i)
	{
		neuron.update_test(I);
	}
	EXPECT_EQ(4, neuron.getNb_Spikes_());
}

/*****************************************************************************************************************************//**
     * we wait for the first spike and see the impact on the other neuron2
     ***************************************************************************************************************************/
     
TEST(TwoNeurons, NoSpike) 
{
	Neuron neuron1, neuron2;
	int delay = 15;
	double I=1.01;
	//we wait for the first spike and see the impact on the other neuron2
	for(int i=0; i<925+delay; ++i)
	{
		neuron1.update_test(I);
		if(neuron1.spike(20))
		{
			neuron1.update_test(I);
			neuron2.receive_spike(0.1,i);
			EXPECT_EQ(0.0, neuron1.getV());
		}	
		neuron2.update_test(0);
	}
	EXPECT_NEAR(0.1, neuron2.getV(),1e-3);
}

TEST(TwoNeurons, WithSpike) 
{
	Neuron neuron1, neuron2;
	int delay = 15;
	double I1=1.01;
	double I2=1.0;
	//we wait for the first spike and see the impact on the other neuron2
	for(int i=0; i<1869+delay; ++i)
	{
		neuron1.update_test(I1);
		if(neuron1.spike(20))
		{
			neuron1.update_test(I1);
			neuron2.receive_spike(0.1,i);
			EXPECT_EQ(0.0, neuron1.getV());
		}	
		neuron2.update_test(I2);
	}
	EXPECT_EQ(1, neuron2.getNb_Spikes_());
	EXPECT_EQ(0, neuron2.getV());
}
	
int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}	
	


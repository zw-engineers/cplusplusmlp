#include <iostream>
#include <string>

#include "Timer.h"
#include "NN.h"
#include <thread>


void Train(NN& nn)
{
	
	for (int i = 0; i < 4000; i++)
	{
		nn.train({ 0.0, 1.0 }, { 1.0 });
		nn.train({ 1.0, 0.0 }, { 1.0 });
		nn.train({ 1.0, 1.0 }, { 0.0 });
		nn.train({ 0.0, 0.0 }, { 0.0 });
	
	}
}

int main()
{
	std::cin.get();
}
#include <iostream>
#include "Patient.h"
#include "Simulator.h"
#include <ctime>


int main()
{
    std::cout << "Hello" << std::endl;
	srand(time(NULL));
	std::cout << std::boolalpha;
	Simulator sim;
	sim.enter_data();
	sim.run_simulation();
	sim.show_stats();
	return 0;
}

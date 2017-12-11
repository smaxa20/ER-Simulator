#include <iostream>
#include "Patient.h"
#include "Simulator.h"

int main()
{
	std::cout << std::boolalpha;
	Simulator sim;
	sim.enter_data();
	sim.run_simulation();
	sim.show_stats();
	return 0;
}
#include <iostream>
#include "Patient.h"

int main()
{
	std::cout << std::boolalpha;
	Patient p1;
	std::cout << p1.getName() << std::endl;
	std::cout << p1.getJackass() << std::endl;
	std::cout << p1.getSeverity() << std::endl;
	std::cout << p1.getInjury() << std::endl;
	return 0;
}
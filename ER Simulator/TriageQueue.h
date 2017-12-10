#pragma once
#include "Patient.h"
#include "Physician.h"
#include <queue>
#include <set>
#include <iterator>
#include <ctime>

class TriageQueue
{
private:
	std::priority_queue<Patient> the_queue;
	int arrival_rate;
	std::multiset<Patient> patients;
public:
	TriageQueue(int arrival_rate) { this->arrival_rate = arrival_rate; }
	int getArrivalRate() { return arrival_rate; }
	void new_patient()
	{
		Patient *p1 = new Patient;
		the_queue.push(*p1);
		patients.insert(*p1);
	}
	void Update(int clock)
	{
		std::multiset<Patient>::iterator it;
		for (it = patients.begin(); it != patients.end(); ++it)
			it->getWaitTime++;
		srand(time(NULL));
		double num = double(rand()) / RAND_MAX;
		if (num < arrival_rate)
			new_patient();
	}
};
#pragma once
#include "Patient.h"
#include "Physician.h"
#include <queue>
#include <vector>
#include <iterator>
#include <ctime>

class TriageQueue
{
private:
	std::priority_queue<Patient> the_queue;
	double arrival_rate;
	std::vector<Patient> patients;
public:
	TriageQueue() { arrival_rate = 0; }
	TriageQueue(int arrival_rate) { this->arrival_rate = arrival_rate; }
	double getArrivalRate() { return arrival_rate; }
	void setArrivalRate(double arrival_rate) { this->arrival_rate = arrival_rate; }
	std::priority_queue<Patient> getQueue() { return the_queue; }
	void new_patient()
	{
		Patient *p1 = new Patient;
		the_queue.push(*p1);
		patients.push_back(*p1);
	}
	//void new_patient(std::string name, int severity, std::string injury, bool isJackass, int treatment_time, int wait_time)
	//{
	//	Patient p1(name, severity, injury, isJackass, treatment_time, wait_time + 1);
	//	the_queue.push(p1);
	//	patients.insert(p1);
	//}
	void Update(int clock)
	{
		for (int i = 0; i < patients.size(); i++)
		{
			patients[i].setWaitTime(patients[i].getWaitTime() + 1);
		}
		double num = double(rand()) / RAND_MAX;
		if (num < arrival_rate)
			new_patient();
	}
};
#pragma once
#include "TriageQueue.h"
#include <vector>
#include "Patient.h"
#include <queue>
#include "Physician.h"
#include <ctime>

class TreatmentQueue
{
private:
	TriageQueue *triage_queue;
	std::vector<Patient> patients;
	std::vector<Doctor> doctors;
	std::vector<Nurse> nurses;
	std::vector<Patient> discharge;
	int num_docs;
	int num_nurses;
	int num_served;
	int total_service_time;
public:
	TreatmentQueue()
	{
		num_docs = 0;
		num_nurses = 0;
		num_served = 0;
		total_service_time = 0;
	}
	TreatmentQueue(int num_docs, int num_nurses, TriageQueue *triage_queue)
	{
		this->triage_queue = triage_queue;
		this->num_docs = num_docs;
		this->num_nurses = num_nurses;
		Doctor *d1 = new Doctor;
		Nurse *n1 = new Nurse;
		for (int i = 0; i < doctors.size(); i++)
		{
			doctors.push_back(*d1);
		}
		for (int i = 0; i < nurses.size(); i++)
		{
			nurses.push_back(*n1);
		}
	}
	void setTriageQueue(TriageQueue triage_queue) { this->triage_queue = &triage_queue; }

	int getDocs() { return num_docs; }
	void setDocs(int docs) { num_docs = docs; }

	int getNurses() { return num_nurses; }
	void setNurses(int nurses) { num_nurses = nurses; }

	int getServed() { return num_served; }
	void setServed(int num_served) { this->num_served = num_served; }

	int getTime() { return total_service_time; }

	void Update(int clock)
	{
		srand(time(NULL));
		for (int i = 0; i < nurses.size(); i++)
		{
			if (!triage_queue->getQueue().empty())
			{
				if (nurses[i].occupied() == false && triage_queue->getQueue().top().severity <= 10)
				{
					nurses[i].setPatient(triage_queue->getQueue().top());
					int num = (rand() % 10) + 1;
					if (nurses[i].getPatient().getJackass() == false)
						nurses[i].getPatient().setTreatmentTime(num);
					else
						nurses[i].getPatient().setTreatmentTime(num * 2);
					patients.push_back(triage_queue->getQueue().top());
					triage_queue->getQueue().pop();
					nurses[i].treatPatient();
				}
			}
		}

		for (int i = 0; i < doctors.size(); i++)
		{
			if (doctors[i].occupied() == false)
			{
				if (!triage_queue->getQueue().empty())
				{
					doctors[i].setPatient(triage_queue->getQueue().top());
					int num = (rand() % 20) + 1;
					if (doctors[i].getPatient().getJackass() == false)
						doctors[i].getPatient().setTreatmentTime(3);
					else
						doctors[i].getPatient().setTreatmentTime(3 * 2);
					patients.push_back(triage_queue->getQueue().top());
					triage_queue->getQueue().pop();
					doctors[i].treatPatient();
				}
			}
		}

		for (int i = 0; i < nurses.size(); i++)
		{
			doctors[i].getPatient().setTreatmentTime(doctors[i].getPatient().getTreatmentTime() - 1);
			total_service_time++;
			if (nurses[i].getPatient().getTreatmentTime() == 0)
			{
				if (i > patients.size())
				{
					discharge.push_back(patients[i]);
					patients.pop_back();
					total_service_time += patients[i].getWaitTime();
				}
				setServed(getServed() + 1);
				nurses[i].setBusy(false);
			}
		}

		for (int i = 0; i < doctors.size(); i++)
		{
			doctors[i].getPatient().setTreatmentTime(doctors[i].getPatient().getTreatmentTime() - 1);
			total_service_time++;
			if (doctors[i].getPatient().getTreatmentTime() == 0)
			{
				if (i > patients.size())
				{
					discharge.push_back(patients[i]);
					patients.pop_back();
					total_service_time += patients[i].getWaitTime();
				}
				setServed(getServed() + 1);
				doctors[i].setBusy(false);
			}
		}
	}
	friend class Simulator;
};
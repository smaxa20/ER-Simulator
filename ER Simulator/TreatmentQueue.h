#pragma once
#include "TriageQueue.h"
#include <vector>
#include "Patient.h"
#include <queue>
#include "Physician.h"

class TreatmentQueue
{
private:
	TriageQueue *triage_queue;
	std::vector<Patient> patients;
	std::vector<Doctor> doctors;
	std::vector<Nurse> nurses;
	int num_docs;
	int num_nurses;
public:
	TreatmentQueue(int num_docs, int num_nurses)
	{
		this->num_docs = num_docs;
		this->num_nurses = num_nurses;
	}
	void setTriageQueue(TriageQueue *triage_queue) { this->triage_queue = triage_queue; }
	void Update(int clock)
	{
		bool free_room;
		for (int i = 0; i < doctors.size(); i++)
		{
			if (doctors[i].getBusy() == false)
				free_room = true;
		}
		for (int i = 0; i < nurses.size(); i++)
		{
			if (nurses[i].getBusy() == false)
				free_room = true;
		}
		if (free_room == true)
		{

			for (int i = 0; i < patients.size(); i++)
				patients[i].getTreatmentTime()--;
		}
	}
};
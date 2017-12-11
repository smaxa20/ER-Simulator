#ifndef PATIENT_H_
#define PATIENT_H_

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <cctype>

class Patient
{
private:
	std::string name;
	int severity;
	std::string injury;
	bool isJackass;
	int treatment_time;
	int wait_time;
public:
	Patient()
	{
		srand(time(NULL));
		std::string line;
		int numOfLines = 0;
		std::ifstream population;
		population.open("Text.txt", std::ios::in);
		int random = rand() % 10;
		while (getline(population, line))
		{
			if (numOfLines == random)
			{
				name = line;
				break;
			}
			numOfLines++;
		}

		int priority = (rand() % 10) + 1;
		if (priority == 1)
			severity = (rand() % 5) + 16;
		else if (priority == 2 || priority == 3)
			severity = (rand() % 5) + 11;
		else
			severity = (rand() % 10) + 1;

		if (severity == 1)
			injury = "Small Abrasion";
		else if (severity == 2)
			injury = "Mild Cold Symptoms";
		else if (severity == 3)
			injury = "Fever";
		else if (severity == 4)
			injury = "Pink Eye";
		else if (severity == 5)
			injury = "Strep Throat";
		else if (severity == 6)
			injury = "Twisted Ankle";
		else if (severity == 7)
			injury = "Constipation";
		else if (severity == 8)
			injury = "Small Laceration";
		else if (severity == 9)
			injury = "Mild Vomiting and Diarrhea";
		else if (severity == 10)
			injury = "Fractured Bone";
		else if (severity == 11)
			injury = "Concussion";
		else if (severity == 12)
			injury = "Ruptured Appendix";
		else if (severity == 13)
			injury = "Severe Dehydration";
		else if (severity == 14)
			injury = "Kidney Failure";
		else if (severity == 15)
			injury = "Neonatal Sepsis";
		else if (severity == 16)
			injury = "Cardiac Tamponade";
		else if (severity == 17)
			injury = "Multiple System Trauma";
		else if (severity == 18)
			injury = "Stroke";
		else if (severity == 19)
			injury = "Epidural Hematoma";
		else if (severity == 20)
			injury = "Cardiac Arrest";

		int num = (rand() % 10) + 1;
		if (num <= 3)
			isJackass = true;
		else
			isJackass = false;
		wait_time = 0;
	}

	std::string getName() { return name; }
	std::string getInjury() { return injury; }
	bool getJackass() { return isJackass; }
	int getTreatmentTime() { return treatment_time; }
	void setTreatmentTime(int treatment_time) { this->treatment_time = treatment_time; }
	int getWaitTime() { return wait_time; }
	void setWaitTime(int wait_time) { this->wait_time = wait_time; }
	int getSeverity() { return severity; }

	bool operator<(const Patient &p1) const {
		return (this->severity < p1.severity); }
	
	//Added by M.Bell as an experiment
	void incWait()  { wait_time++; }
	friend class TriageQueue;
	friend class TreatmentQueue;
};

#endif
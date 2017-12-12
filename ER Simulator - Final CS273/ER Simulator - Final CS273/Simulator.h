#pragma once
#include "TriageQueue.h"
#include "TreatmentQueue.h"
#include <string>
using std::cout;
using std::endl;

class Simulator
{
private:
	int total_time;
	int clock;
	TriageQueue *triage_queue;
	TreatmentQueue *treatment_queue;
	bool list = false;
public:
	Simulator() {}
	int read_int(const std::string &prompt, int low, int high)
	{
		if (low >= high) // invalid range
			throw std::invalid_argument("invalid range specified");

		std::cin.exceptions(std::ios_base::failbit);
		int num = 0;
		while (true) {
			try {
				while (true) {
					std::cout << prompt;
					std::cin >> num;
					if (num >= low && num <= high) { // within the specified range
						std::cout << std::endl;
						return num;
					}
				}
			}
			catch (std::ios_base::failure) {
				std::cout << "Bad numeric string -- try again\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			}
		}
	}

	void enter_data()
	{
		cout << "This is an ER simulator." << endl;
		cout << "This simulator assumes that the patient arrival rate will be at most 60 patients per hour." << endl;
		cout << "This simulator also assumes that there will be at least one doctor and at least one nurse on duty at all times." << endl;

		double rate = read_int("Please enter your desired patient arrival rate: ", 1, 60);
		double arrival_rate = rate / 60.0;

		int num_docs = read_int("Please enter your desired number of doctors: ", 1, INT_MAX);
		int num_nurses = read_int("Please enter your desired number of nurses: ", 1, INT_MAX);

		total_time = read_int("Please enter your desired simulation time: ", 168, INT_MAX);
		total_time *= 60;

		// set the patient arrival rate for the triage_queue
		triage_queue = new TriageQueue(arrival_rate);
		triage_queue->setArrivalRate(arrival_rate);

		// set the number of doctors and nurses 
		treatment_queue = new TreatmentQueue(num_docs, num_nurses, triage_queue);
	}
	void show_stats()
	{
		cout << "Number of patients treated: " << treatment_queue->getServed() << endl;
		cout << "Average visit time: " << treatment_queue->getTime() / treatment_queue->getServed() << endl;
		char menu = ' ';
		do
		{
			if (list == false)
			{
				cout << "Choose what to do next:" << endl;
				cout << "    a. Terminate Program" << endl;
				cout << "    b. Search by name" << endl;
				cout << "    c. List Names" << endl;

				std::string name;
				std::cin >> menu;
				switch (menu)
				{
				case 'a':
					break;
				case 'b':
					cout << "Enter a name: ";
					std::cin >> name;
					search_by_name(name);
					break;
				case 'c':
					list_names();
					break;
				}
			}
			else if (list == true)
			{
				cout << "Choose what to do next:" << endl;
				cout << "    a. Terminate Program" << endl;
				cout << "    b. Search by Name" << endl;

				char menu;
				std::string name;
				switch (menu)
				{
				case 'a':
					break;
				case 'b':
					cout << "Enter a name: ";
					std::cin >> name;
					search_by_name(name);
					break;
				}
			}
		} while (menu != 'a');
	}
	void search_by_name(std::string name)
	{
		for (int i = 0; i < treatment_queue->discharge.size(); i++)
		{
			if (treatment_queue->discharge[i].getName() == name)
			{
				cout << "Name: " << treatment_queue->discharge[i].getName() << endl;
				cout << "Injury: " << treatment_queue->discharge[i].getInjury() << endl;
				cout << "Jackass?: " << treatment_queue->discharge[i].getJackass() << endl;
				cout << "Treatment Time: " << treatment_queue->discharge[i].getTreatmentTime() << endl;
			}
		}
		
	}

	void list_names()
	{
		for (int i = 0; i < treatment_queue->discharge.size(); i++)
		{
			cout << "Name: " << treatment_queue->discharge[i].getName() << endl;
		}
	}

	void run_simulation()
	{
		for (clock = 0; clock < total_time; clock++)
		{
			this->triage_queue->Update(clock);
			this->treatment_queue->Update(clock);
		}
	}
};

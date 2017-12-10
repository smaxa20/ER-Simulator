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

	void enter_date()
	{
		cout << "This is an ER simulator." << endl;
		cout << "This simulator assumes that the patient arrival rate will be at most 60 patients per hour." << endl;
		cout << "This simulator also assumes that there will be at least one doctor and at least one nurse on duty at all times." << endl;

		int rate = read_int("Please enter your desired patient arrival rate: ", 1, 60);
		double arrival_rate = rate / 60.0;

		int num_docs = read_int("Please enter your desired number of doctors: ", 1, INT_MAX);
		int num_nurses = read_int("Please enter your desired number of nurses: ", 1, INT_MAX);

		total_time = read_int("Please enter your desired simulation time: ", 168, INT_MAX);
		total_time *= 60;

		// set the patient arrival rate for the triage_queue
		triage_queue->setArrivalRate(arrival_rate);

		// set the number of doctors and nurses 
		treatment_queue->setDocs(num_docs);
		treatment_queue->setNurses(num_nurses);
	}
	void show_stats()
	{
		cout << "Number of patients treated: " << treatment_queue->getServed() << endl;
		cout << "Average visit time: " << treatment_queue->getTime() / treatment_queue->getServed() << endl;

		if (list == false)
		{
			cout << "Choose what to do next:" << endl;
			cout << "    a. List names" << endl;
			cout << "    b. Search by name" << endl;
			cout << "    c. Terminate Program" << endl;

			char menu;
			std::string name;
			switch (menu)
			{
			case 'a':
				cout << "Enter a name: ";
				std::cin >> name;
				search_by_name(name);
				break;
			case 'b':
				list_names();
				break;
			case 'c':
				break;
			}
		}
		else if (list == true)
		{
			cout << "Choose what to do next:" << endl;
			cout << "    a. Search by name" << endl;
			cout << "    b. Terminate Program" << endl;

			char menu;
			std::string name;
			switch (menu)
			{
			case 'a':
				cout << "Enter a name: ";
				std::cin >> name;
				search_by_name(name);
				break;
			case 'b':
				break;
			}
		}
	}
	void search_by_name(std::string);
	void list_names();
};
#pragma once
#include "Patient.h"

class Physician
{
private:
	Patient patient;
	bool isBusy;
public:
	virtual void treatPatient() = 0;
	virtual Patient getPatient() = 0;
	virtual bool getBusy() = 0;
};


class Doctor : public Physician
{
private:
	Patient patient;
	bool isBusy;
public:
	Doctor() { isBusy = false; }
	void treatPatient() { isBusy = true; }
	Patient getPatient() { return patient; }
	Patient setPatient(Patient p1) { this->patient = p1; }
	bool getBusy() { return isBusy; }
};


class Nurse : public Physician
{
private:
	Patient patient;
	bool isBusy;
public:
	Nurse() { isBusy = false; }
	void treatPatient() { isBusy = true; }
	Patient getPatient() { return patient; }
	Patient setPatient(Patient p1) { this->patient = p1; }
	bool getBusy() { return isBusy; }
};
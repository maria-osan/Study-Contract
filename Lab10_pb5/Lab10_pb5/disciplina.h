#pragma once

#include <string>
#include <iostream>

using std::string;

class DisciplinaException {
	string msg;

public:
	DisciplinaException(const string& m) : msg{ m } {};
	
	string getMsg() const {
		return msg;
	}
};

class Disciplina {
private:
	string id; // the code of the subject
	string name; // the name of the subject
	string nr_hours; // the number of hours per week
	string type; // the type of the subject
	string teacher; // the name of the teacher

public:
	//default constructor
	//Disciplina() = default;

	Disciplina(const string i, const string n, const string h, const string t, const string teach) : id{ i }, name{ n }, nr_hours{ h }, type{ t }, teacher{ teach } {}

	// copy constructor
	Disciplina(const Disciplina& d) : id{ d.id }, name{ d.name }, nr_hours{ d.nr_hours }, type{ d.type }, teacher{ d.teacher } {
		//std::cout << "!!!!!\n";
	}


	// ---GETTERS---

	string get_id() const
	{
		// Getter for the id of the subject
		return id;
	}

	string get_name() const
	{
		// Getter for the name of the subject
		return name;
	}

	string get_nr_hours() const
	{
		//Getter for the number of hours
		return nr_hours;
	}

	string get_type() const
	{
		// Getter for the type of the subject
		return type;
	}

	string get_teacher() const
	{
		// Getter for the name of the teacher of the subject
		return teacher;
	}

	// ---SETTERS---
	void set_name(string new_val)
	{
		// Setter for the name of the subject
		// new_val : string (the new name of the subject)
		this->name = new_val;
	}

	void set_nr_hours(string new_val)
	{
		// Setter for the number of hours
		// new_val : string (the new number of hours)
		this->nr_hours = new_val;
	}

	void set_type(string new_val)
	{
		// Setter for the type of the subject
		// new_val : string (the new type of the subject)
		this->type = new_val;
	}

	void set_teacher(string new_val)
	{
		// Setter for the name of the teacher of the subject
		// new_val : string (the new type of the subject)
		this->teacher = new_val;
	}
};

// compare after the subject name
// return true if d1 is smaller than d2
bool cmp_name(const Disciplina& d1, const Disciplina& d2);
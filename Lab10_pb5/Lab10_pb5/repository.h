#pragma once

#include "disciplina.h"

#include <vector>
#include <string>
#include <ostream>
#include <functional>
#include <map>

using std::vector;
using std::string;
using std::ostream;
using std::function;

class Repo {
	vector<Disciplina> all;

	// private method that checks if d already exists in the repository
	bool exist(const Disciplina& d) const;

public:
	Repo() = default;

	// does not allow copying of objects
	Repo(const Repo& d) = delete;

	virtual ~Repo() = default;

	// saving subject
	// throw an exception if there is another subject with the same id
	//void store(const Disciplina& d);
	virtual void store(const Disciplina& d);

	// search
	// throw an exception is the subject does not exist
	const Disciplina& find(string id) const;

	// delete
	// throw an exception is the subject does not exist in the vector
	// void del(const Disciplina& d);
	virtual void del(const Disciplina& d);

	// void modify(const Disciplina& d, const string& new_val, char opt);
	virtual void modify(const Disciplina& d, const string& new_val, char opt);

	// return all the subjects saved
	const vector<Disciplina>& get_all() const noexcept;

	std::map<string, int> raport();
};

// used to signal exceptional situations that may appear in the repo
class RepoException {
	string msg;

public:
	RepoException(string m) : msg{ m } {}

	string get_msg() const
	{
		return msg;
	}

	// friend function (I want to use private member msg)
	friend ostream& operator<<(ostream& out, const RepoException& exp);
};

ostream& operator<<(ostream& out, const RepoException& exp);


// ---TESTS---
void tests_repo();


class RepoFile :public Repo
{
private:
	string file_name;
	void load_from_file();
	void write_to_file();

public:
	RepoFile(string f_name) :Repo(), file_name{ f_name }
	{
		load_from_file(); // loading the datas from the file
	}

	void store(const Disciplina& d) override
	{
		Repo::store(d); // calling the method from the base class
		write_to_file();
	}

	void del(const Disciplina& d) override
	{
		Repo::del(d); // calling the method from the base class
		write_to_file();
	}

	void modify(const Disciplina& d, const string& new_val, char opt) override
	{
		Repo::modify(d, new_val, opt);
		write_to_file();
	}
};
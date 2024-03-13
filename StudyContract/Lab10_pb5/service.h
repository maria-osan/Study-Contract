#pragma once

#include "disciplina.h"
#include "repository.h"
#include "validator.h"
#include "undo.h"
#include "study_contract.h"
#include "export.h"

#include <string>
#include <vector>
#include <functional>
#include <map>

using std::vector;
using std::string;

class Service {
	Repo& r;
	ValidateDisciplina& val;

	vector<std::unique_ptr<Undo>> undo_actions;

	study_contract lst;

	// General filtering function
	// cmp_f - function that compares 2 subjects, checks if the criteria occurs
	//       - it can be any function (outside the class) that respects the signature (returns bool and has 2 subject parameters)
	//       - it can be a lambda function (which does not capture anything in the capture list)
	// return only the subjects that pass the filter (fct(d) == true)
	vector<Disciplina> filter(function<bool(const Disciplina&)> fct);

	// General sorting function
	// cmp_f - function that compares 2 subjects, checks if the criteria occurs
	//       - it can be any function (outside the class) that respects the signature (returns bool and has 2 subject parameters)
	//       - it can be a lambda function (which does not capture anything in the capture list)
	// returns a list sorted by the criteria given as a parameter
	vector<Disciplina> general_sort(bool (*cmp_f)(const Disciplina&, const Disciplina&));

public:
	Service(Repo& rep, ValidateDisciplina& v) noexcept : r{ rep }, val{ v } {}

	// does not allow copying of Service objects
	Service(const Service& ot) = delete;

	// return all the subjects in the added order
	const vector<Disciplina>& get_all() noexcept {
		return r.get_all();
	}

	// add a new subject
	// throw exception if: it can't be saved, it's invalid
	void add(const string& id, const string& name, const string& nr_hours, const string& type, const string& teacher);

	// delete a subject
	// throw an exception is the subject does not exist in the vector
	void del(string id);

	// search for a subject
	// throw an exception is the subject doesn't exist
	const Disciplina& find(string id) const;

	void modify(const Disciplina& d, const string& new_val, char opt);

	// sort by subject name
	vector<Disciplina> sort_name();

	// sort by number of hours per week and id
	vector<Disciplina> sort_hours();

	// sort by teacher and type
	vector<Disciplina> sort_teacher_type();

	// return only the subjects that has the number of hours per week equal with a given one
	vector<Disciplina> filter_equal_hours(const string& nr_hours);

	// return only the subjects that has the same teacher as a given one
	vector<Disciplina> filter_same_teacher(const string& teacher);

	std::map<string, int> raport();

	void undo();

	const vector<Disciplina>& addStudyContract(const string& id);

	const vector<Disciplina>& addRandom(int nr);

	const vector<Disciplina>& emptyStudyContract();

	const vector<Disciplina>& getAllStudyContract();

	string exportContractHTML(string fName);

	study_contract& getContract()
	{
		return lst;
	}
};

void tests_service();
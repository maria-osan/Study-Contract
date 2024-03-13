#include "service.h"

#include <assert.h>
#include <iostream>
#include <sstream>
#include <functional>
#include <algorithm>

using std::ostream;
using std::stringstream;


// add a new sunject
// throw exception if: it can't be saved, it's invalid
void Service::add(const string& id, const string& name, const string& nr_hours, const string& type, const string& teacher)
{
	Disciplina d{ id, name, nr_hours, type, teacher };
	val.validate(d);
	r.store(d);

	undo_actions.push_back(std::make_unique<UndoAdd>(r, d));
}

// delete a subject
// throw an exception is the subject does not exist in the vector
void Service::del(string id)
{
	Disciplina d = r.find(id);
	undo_actions.push_back(std::make_unique<UndoDelete>(r, d));
	r.del(d);
}

// search for a subject
// throw an exception is the subject doesn't exist
const Disciplina& Service::find(string id) const
{
	return r.find(id);
}

void Service::modify(const Disciplina& d, const string& new_val, char opt)
{
	if (opt == '1')
	{
		Disciplina d1{ d.get_id(), new_val, d.get_nr_hours(), d.get_type(), d.get_teacher() };
		undo_actions.push_back(std::make_unique<UndoModify>(r, d1, d.get_name(), opt));
	}
	else if (opt == '2')
	{
		Disciplina d1{ d.get_id(), d.get_name(), new_val , d.get_type(), d.get_teacher() };
		undo_actions.push_back(std::make_unique<UndoModify>(r, d1, d.get_nr_hours(), opt));
	}
	else if (opt == '3')
	{
		Disciplina d1{ d.get_id(), d.get_name(), d.get_nr_hours(), new_val, d.get_teacher() };
		undo_actions.push_back(std::make_unique<UndoModify>(r, d1, d.get_type(), opt));
	}
	else {
		Disciplina d1{ d.get_id(), d.get_name(), d.get_nr_hours(), d.get_type(), new_val };
		undo_actions.push_back(std::make_unique<UndoModify>(r, d1, d.get_teacher(), opt));
	}

	r.modify(d, new_val, opt);
}

void Service::undo()
{
	if (undo_actions.empty())
	{
		throw RepoException{ "Nu se mai poate efectua undo" };
	}
	undo_actions.back()->do_undo();
	undo_actions.pop_back();
}

//vector<Disciplina> Service::filter(function<bool(const Disciplina&)> fct)
//{
//	vector<Disciplina> rez;
//	for (const auto& d : r.get_all())
//		if (fct(d))
//			rez.push_back(d);
//
//	return rez;
//}

// filter after number of hours per week
vector<Disciplina> Service::filter_equal_hours(const string& nr_hours)
{
	/*return filter([nr_hours](const Disciplina& d) {
		return d.get_nr_hours() == nr_hours;
		});*/

	vector<Disciplina> rez;

	std::copy_if(r.get_all().begin(), r.get_all().end(), std::back_inserter(rez), [nr_hours](const Disciplina& d) {
		return d.get_nr_hours() == nr_hours;
		});

	return rez;
}

// filter after teacher
vector<Disciplina> Service::filter_same_teacher(const string& teacher)
{
	/*return filter([teacher](const Disciplina& d) {
		return d.get_teacher() == teacher;
		});*/

	vector<Disciplina> rez;

	std::copy_if(r.get_all().begin(), r.get_all().end(), std::back_inserter(rez), [teacher](const Disciplina& d) {
		return d.get_teacher() == teacher;
		});

	return rez;
}

//vector<Disciplina> Service::general_sort(bool(*cmp_f)(const Disciplina&, const Disciplina&))
//{
//	vector<Disciplina> v{ r.get_all() }; // a copy is made
//	for (size_t i = 0; i < v.size(); i++)
//		for (size_t j = 0; j < v.size(); j++)
//			if (!cmp_f(v[i], v[j]))
//			{
//				// switch the subjects
//				Disciplina aux = v[i];
//				v[i] = v[j];
//				v[j] = aux;
//			}
//	return v;
//}

// sort by subject name
vector<Disciplina> Service::sort_name()
{
	auto copy_all = r.get_all();
	std::sort(copy_all.begin(), copy_all.end(), cmp_name);
	return copy_all;
}

// sort by number of hours per week and id
vector<Disciplina> Service::sort_hours()
{
	/*return general_sort([](const Disciplina& d1, const Disciplina& d2) {
		if (d1.get_nr_hours() == d2.get_nr_hours()) {
			return d1.get_id() > d2.get_id();
		}
		return d1.get_nr_hours() > d2.get_nr_hours();
		});*/

	auto copy_all = r.get_all();

	std::sort(copy_all.begin(), copy_all.end(), [](const Disciplina& d1, const Disciplina& d2) {
		if (d1.get_nr_hours() == d2.get_nr_hours()) {
			return d1.get_id() < d2.get_id();
		}
		return d1.get_nr_hours() < d2.get_nr_hours();
		});

	return copy_all;
}

// sort by teacher and type
vector<Disciplina> Service::sort_teacher_type()
{
	/*return general_sort([](const Disciplina& d1, const Disciplina& d2) {
		if (d1.get_teacher() == d2.get_teacher()) {
			return d1.get_type() > d2.get_type();
		}
		return d1.get_teacher() > d2.get_teacher();
		});*/

	auto copy_all = r.get_all();

	std::sort(copy_all.begin(), copy_all.end(), [](const Disciplina& d1, const Disciplina& d2) {
		if (d1.get_teacher() == d2.get_teacher()) {
			return d1.get_type() < d2.get_type();
		}
		return d1.get_teacher() < d2.get_teacher();
		});

	return copy_all;
}

std::map<string, int> Service::raport()
{
	return r.raport();
}

const vector<Disciplina>& Service::addStudyContract(const string& id)
{
	const Disciplina& d = r.find(id);
	lst.add(d);
	return lst.get_list();
}

const vector<Disciplina>& Service::addRandom(int nr)
{
	lst.generate(nr, r.get_all());
	return lst.get_list();
}

const vector<Disciplina>& Service::emptyStudyContract()
{
	lst.empty_list();
	return lst.get_list();
}

const vector<Disciplina>& Service::getAllStudyContract()
{
	return lst.get_list();
}

string Service::exportContractHTML(string fName)
{
	export_to_html(fName, lst.get_list());
	return "";
}

// ---TESTS---

void test_add_serv()
{
	// Test for functoin: add
	Repo r;
	ValidateDisciplina val;
	Service srv{ r,val };
	assert(srv.get_all().size() == 0);

	srv.add("5006", "POO", "1", "seminar", "Czibula Istvan");
	assert(srv.get_all().size() == 1);

	// I try to add something invalid
	try {
		srv.add("5006", "POO", "-1", "semi", "");
	}
	catch (ValidateException&) {
		assert(true);
	}

	// I try to add something that already exist
	try {
		srv.add("5006", "POO", "1", "semi", "Czibula Istvan");
	}
	catch (const RepoException&) {
		assert(true);
	}
}

void test_search_serv()
{
	// Test for functoin: find
	Repo r;
	ValidateDisciplina val;
	Service srv{ r,val };
	srv.add("5006", "POO", "1", "seminar", "Czibula Istvan");
	srv.add("5022", "SDA", "1", "laborator", "Maier Mariana");

	auto d = srv.find("5006");
	assert(d.get_id() == "5006");
	assert(d.get_name() == "POO");
	assert(d.get_nr_hours() == "1");
	assert(d.get_type() == "seminar");
	assert(d.get_teacher() == "Czibula Istvan");

	// throw exception if it doesn't exist
	try {
		srv.find("5026");
	}
	catch (RepoException&) {
		assert(true);
	}
}

void test_delete_serv()
{
	// Test for function: del
	Repo r;
	ValidateDisciplina val;
	Service srv{ r,val };
	srv.add("5006", "POO", "1", "seminar", "Czibula Istvan");
	srv.add("5022", "SDA", "1", "laborator", "Maier Mariana");

	srv.del("5006");
	assert(r.get_all().size() == 1);

	r.del(r.find("5022"));
	assert(srv.get_all().size() == 0);

	// I can't delete a subject that doesn't exist in the vector
	try {
		srv.del("5006");
	}
	catch (const RepoException& e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}
}

void test_modify_serv()
{
	// Test for function: modify
	Repo r;
	ValidateDisciplina val;
	Service srv{ r,val };
	Disciplina d = { "5006", "POO", "1", "seminar", "Czibula Istvan" };
	srv.add("5006", "POO", "1", "seminar", "Czibula Istvan");
	Disciplina d2 = { "5022", "SDA", "1", "laborator", "Maier Mariana" };
	srv.add("5022", "SDA", "1", "laborator", "Maier Mariana");

	const string& name = "FP";
	srv.modify(d, name, '1');
	assert(r.get_all()[0].get_name() == "FP");

	const string& nr_hours = "2";
	srv.modify(d, nr_hours, '2');
	assert(r.get_all()[0].get_nr_hours() == "2");

	const string& type = "curs";
	srv.modify(d2, type, '3');
	assert(r.get_all()[1].get_type() == "curs");

	const string& teacher = "Czibula Istvan";
	srv.modify(d2, teacher, '4');
	assert(r.get_all()[1].get_teacher() == "Czibula Istvan");
}


void test_filter() {
	// Test for functions: filter_equal_hours, filter_same_teacher
	Repo r;
	ValidateDisciplina val;
	Service srv{ r,val };
	srv.add("5006", "POO", "1", "seminar", "Czibula Istvan");
	srv.add("5022", "SDA", "1", "laborator", "Maier Mariana");
	srv.add("0014", "Geometrie", "2", "curs", "Blaga Paul");

	assert(srv.filter_equal_hours("1").size() == 2);
	assert(srv.filter_equal_hours("2").size() == 1);
	assert(srv.filter_same_teacher("Czibula Istvan").size() == 1);
	assert(srv.filter_same_teacher("Maier Mariana").size() == 1);
	assert(srv.filter_same_teacher("Blaga Paul").size() == 1);
}

void test_sort() {
	// Test for sort functions
	Repo r;
	ValidateDisciplina val;
	Service srv{ r,val };
	srv.add("5006", "POO", "1", "seminar", "Czibula Istvan");
	srv.add("5022", "SDA", "1", "laborator", "Maier Mariana");
	srv.add("0014", "Geometrie", "2", "curs", "Blaga Paul");
	srv.add("0015", "Geometrie", "2", "seminar", "Blaga Paul");

	auto first_d = srv.sort_name()[0];
	assert(first_d.get_name() == "Geometrie");

	first_d = srv.sort_hours()[0];
	assert(first_d.get_nr_hours() == "1");
	assert(first_d.get_id() == "5006");

	first_d = srv.sort_teacher_type()[0];
	assert(first_d.get_teacher() == "Blaga Paul");
	assert(first_d.get_type() == "curs");

}

void test_rapot_serv()
{
	// test for function: raport
	Repo r;
	ValidateDisciplina val;
	Service srv{ r,val };
	srv.add("5006", "POO", "1", "seminar", "Czibula Istvan");
	srv.add("5022", "SDA", "1", "laborator", "Maier Mariana");
	srv.add("2014", "Geometrie", "2", "seminar", "Blaga Cristina");
	srv.add("0014", "Geometrie", "2", "curs", "Blaga Paul");

	std::map<string, int> rap = srv.raport();
	assert(rap["seminar"] == 2);
	assert(rap["curs"] == 1);
}

void test_undo()
{
	// Test fot undo
	Repo r;
	ValidateDisciplina val;
	Service srv{ r,val };
	Disciplina d = { "5006", "POO", "1", "seminar", "Czibula Istvan" };

	// add
	srv.add("5006", "POO", "1", "seminar", "Czibula Istvan");
	srv.add("5022", "SDA", "1", "laborator", "Maier Mariana");
	assert(r.get_all().size() == 2);
	srv.undo();
	assert(r.get_all().size() == 1);

	// modify
	srv.modify(d, "FP", '1');
	assert(r.get_all()[0].get_name() == "FP");
	srv.undo();
	assert(r.get_all()[0].get_name() == "POO");

	// delete
	srv.del("5006");
	assert(r.get_all().size() == 0);
	srv.undo();
	assert(r.get_all().size() == 1);
	srv.undo();

	// no more undo posible
	try {
		srv.undo();
	}
	catch (RepoException&) {
		assert(true);
	}
}

void tests_service()
{
	test_add_serv();
	test_search_serv();
	test_delete_serv();
	test_modify_serv();
	test_filter();
	test_sort();
	test_rapot_serv();
	test_undo();
}
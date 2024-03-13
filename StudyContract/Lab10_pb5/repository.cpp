#include "repository.h"

#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using std::ostream;
using std::stringstream;
using std::vector;


void RepoFile::load_from_file()
{
	std::ifstream fin(file_name);

	if (!fin.is_open()) // verify if the stream is opened
	{
		throw RepoException("Nu s-a putut deschide fisierul: " + file_name);
	}

	while (!fin.eof())
	{
		std::string id, name, nr_hours, type, first_name, surname, teacher;
		fin >> id >> name >> nr_hours >> type >> surname >> first_name;
		teacher = surname + " " + first_name;

		Disciplina d{ id.c_str(), name.c_str(), nr_hours.c_str(), type.c_str(), teacher.c_str() };
		Repo::store(d);
	}

	fin.close();
}

void RepoFile::write_to_file()
{
	std::ofstream fout(file_name);
	if (!fout.is_open()) //verify if the stream is opened
	{
		throw RepoException("Nu s-a putut deschide fisierul: " + file_name);
	}

	//const vector<Disciplina>& all = Repo::get_all();
	int lines = 0;
	for (auto d : Repo::get_all())
	{
		if (lines < Repo::get_all().size() - 1)
			fout << d.get_id() << " " << d.get_name() << " " << d.get_nr_hours() << " " << d.get_type() << " " << d.get_teacher() << "\n";
		else
			fout << d.get_id() << " " << d.get_name() << " " << d.get_nr_hours() << " " << d.get_type() << " " << d.get_teacher();
		lines++;
	}

	fout.close();
}


// Add 
void Repo::store(const Disciplina& d)
{
	if (exist(d))
	{
		throw RepoException("Exista deja disciplina: " + d.get_name() + " cu id-ul: " + d.get_id());
	}
	all.push_back(d);
}

bool Repo::exist(const Disciplina& d) const
{
	//try
	//{
	//	find(d.get_id());
	//	return true;
	//}
	//catch (RepoException&)
	//{
	//	return false;
	//}

	auto rez = std::find_if(all.begin(), all.end(), [d](const Disciplina& dis) {
		return d.get_id() == dis.get_id();
		});

	if (rez != all.end())
		return true;
	else return false;}

// Search
// throw exception if the subject doesn't exist
const Disciplina& Repo::find(string id) const
{
	for (const auto& d : all)
	{
		if (d.get_id() == id)
			return d;
	}
	// if it doesn't exist throw an exception
	throw RepoException("Nu exista disciplina cu id-ul: " + id);}

// Delete
// throw an exception is the subject doesn't exist
void Repo::del(const Disciplina& d)
{
	if (!exist(d))
	{
		throw RepoException("Nu exista disciplina cu id-ul: " + d.get_id());
	}
	int i = 0;
	for (const auto& dis : all)
	{
		if (d.get_id() == dis.get_id())
			all.erase(all.begin() + i);
		i++;
	}
}

void Repo::modify(const Disciplina& d, const string& new_val, char opt)
{
	for (auto& dis : all)
	{
		if (d.get_id() == dis.get_id())
		{
			if (opt == '1')
				dis.set_name(new_val);
			else if (opt == '2')
				dis.set_nr_hours(new_val);
			else if (opt == '3')
				dis.set_type(new_val);
			else dis.set_teacher(new_val);
		}
	}
}

// return all of the saved subjects
const vector<Disciplina>& Repo::get_all() const noexcept
{
	return all;
}

std::map<string, int> Repo::raport()
{
	std::map<string, int> map;
	for (int i = 0; i < all.size(); i++)
	{
		Disciplina d = all[i];
		auto it = map.find(d.get_type());
		if (it != map.end())
			it->second++;
		else
			map.insert(std::pair<string, int>(d.get_type(), 1));
	}
	return map;
}


ostream& operator<<(ostream& out, const RepoException& exp)
{
	out << exp.msg;
	return out;
}


// ---TESTS---

void test_add()
{
	// Test for functoin: store
	Repo r;
	r.store(Disciplina{ "5006", "POO", "1", "seminar", "Czibula Istvan" });
	assert(r.get_all().size() == 1);
	assert(r.find("5006").get_name() == "POO");

	r.store(Disciplina{ "5022", "SDA", "1", "laborator", "Maier Mariana" });
	assert(r.get_all().size() == 2);

	// I can't add 2 with the same id
	try {
		r.store(Disciplina{ "5006", "POO", "1", "seminar", "Czibula Istvan" });
	}
	catch (const RepoException&) {
		assert(true);
	}

	// search for a sunject that doesn't exist
	try {
		r.find("5026");
	}
	catch (const RepoException& e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}
}

void test_search()
{
	// Test for functoin: find
	Repo r;
	r.store(Disciplina{ "5006", "POO", "1", "seminar", "Czibula Istvan" });
	r.store(Disciplina{ "5022", "SDA", "1", "laborator", "Maier Mariana" });

	auto d = r.find("5006");
	assert(d.get_id() == "5006");
	assert(d.get_name() == "POO");
	assert(d.get_nr_hours() == "1");
	assert(d.get_type() == "seminar");
	assert(d.get_teacher() == "Czibula Istvan");

	// throw exception if it doesn't exist
	try {
		r.find("5026");
	}
	catch (RepoException&) {
		assert(true);
	}
}

void test_delete()
{
	// Test for function: del
	Repo r;
	r.store(Disciplina{ "5006", "POO", "1", "seminar", "Czibula Istvan" });
	r.store(Disciplina{ "5022", "SDA", "1", "laborator", "Maier Mariana" });
	assert(r.get_all().size() == 2);

	r.del(r.find("5006"));
	assert(r.get_all().size() == 1);

	r.del(r.find("5022"));
	assert(r.get_all().size() == 0);

	// I can't delete a subject that doesn't exist in the vector
	try {
		r.del(Disciplina{ "5006", "POO", "1", "seminar", "Czibula Istvan" });
	}
	catch (const RepoException& e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}
}

void test_modify()
{
	// Test for function: modify
	Repo r;
	Disciplina d = { "5006", "POO", "1", "seminar", "Czibula Istvan" };
	r.store(d);
	Disciplina d2 = { "5022", "SDA", "1", "laborator", "Maier Mariana" };
	r.store(d2);

	const string& name = "FP";
	r.modify(d, name, '1');
	assert(r.get_all()[0].get_name() == "FP");

	const string& nr_hours = "2";
	r.modify(d, nr_hours, '2');
	assert(r.get_all()[0].get_nr_hours() == "2");

	const string& type = "curs";
	r.modify(d2, type, '3');
	assert(r.get_all()[1].get_type() == "curs");

	const string& teacher = "Czibula Istvan";
	r.modify(d2, teacher, '4');
	assert(r.get_all()[1].get_teacher() == "Czibula Istvan");
}

void test_raport()
{
	// test for function: raport
	Repo r;
	Disciplina d = { "5006", "POO", "1", "seminar", "Czibula Istvan" };
	r.store(d);
	Disciplina d2 = { "5022", "SDA", "1", "laborator", "Maier Mariana" };
	r.store(d2);
	Disciplina d3 = { "2014", "Geometrie", "2", "seminar", "Blaga Cristina" };
	r.store(d3);
	Disciplina d4 = { "0014", "Geometrie", "2", "curs", "Blaga Paul" };
	r.store(d4);

	std::map<string, int> rap = r.raport();
	assert(rap["seminar"] == 2);
	assert(rap["curs"] == 1);
}

void test_repo_file()
{
	try {
		RepoFile repo{ "test_file,txt" };
	}
	catch (RepoException&) {
		assert(true);
	}

	RepoFile repo{ "test.txt" };

	Disciplina d1 = { "5062", "SDA", "1", "seminar", "Miholca Diana" };
	Disciplina d2 = { "2014", "Geometrie", "2", "seminar", "Blaga Cristina" };

	//test for store
	assert(repo.get_all().size() == 5);
	repo.store(d1);
	repo.store(d2);

	//teste pentru find
	repo.find(d1.get_id());

	//test getAll
	assert(repo.get_all().size() == 7);

	//test modify
	repo.modify(d1, "POO", '1');
	assert(repo.get_all()[0].get_name() == "POO");


	//teste pentru delete
	repo.del(d1);
	repo.del(d2);
	assert(repo.get_all().size() == 5);
}

void tests_repo()
{
	test_add();
	test_search();
	test_delete();
	test_modify();
	test_raport();
	test_repo_file();
}
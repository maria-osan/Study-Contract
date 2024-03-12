#include "study_contract.h"
#include "repository.h"

#include <random>
#include <fstream>
#include <assert.h>

void study_contract::empty_list() noexcept {
	this->list.clear();
	//notify if something change in the contract
	notify();
}

void study_contract::add(Disciplina d)
{
	this->list.push_back(d);
	//notify if something change in the contract
	notify();
}

void study_contract::generate(int nr, vector<Disciplina> v)
{
	this->empty_list();

	// auto seed = chrono::system_clock::now().time_since_epoch().count();
	//shuffle(v.begin(), v.end(), default_random_engine(time(0)));

	for (int i = 0; i < nr && !v.empty(); i++)
	{
		int rnd = rand() % v.size();
		this->add(v.at(rnd));

		v.erase(v.begin() + rnd);
	}
	//notify if something change in the contract
	notify();
}

const vector<Disciplina>& study_contract::get_list()
{
	return this->list;
}

int study_contract::dim()
{
	return this->get_list().size();
}

string study_contract::export_html(string name_file)
{
	export_to_html(name_file, this->get_list());
	return "";
}


void teste_cos()
{
	study_contract s;

	// test add
	Disciplina d1 = { "5006", "POO", "1", "seminar", "Czibula Istvan" };
	s.add(d1);
	assert(s.get_list()[0].get_id() == "5006");
	assert(s.dim() == 1);

	Disciplina d2 = { "5022", "SDA", "1", "laborator", "Maier Mariana" };
	s.add(d2);
	assert(s.get_list()[1].get_name() == "SDA");
	assert(s.dim() == 2);

	// test empty_list
	s.empty_list();
	assert(s.dim() == 0);

	// test generate
	Repo r;
	r.store(d1);
	r.store(d2);
	s.generate(2, r.get_all());
	assert(s.get_list()[0].get_id() == "5006" || s.get_list()[0].get_id() == "5022");

	// test export
	s.add(d1);
	s.add(d2);
	assert(s.export_html("files.html") == "");
	s.empty_list();
}
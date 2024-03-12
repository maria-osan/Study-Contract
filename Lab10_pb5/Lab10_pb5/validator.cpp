#include "validator.h"

#include <assert.h>
#include <sstream>

int validate_id(const string& id)
{
	if (id.size() != 4)
		return 0;
	return 1;
}

void ValidateDisciplina::validate(const Disciplina& d)
{
	vector<string> msgs;
	if (!validate_id(d.get_id()))
		msgs.push_back("ID-ul este invalid!!");
	if (d.get_name().size() == 0)
		msgs.push_back("Denumire disciplina vida!!");
	if (d.get_nr_hours() != "1" && d.get_nr_hours() != "2")
		msgs.push_back("Numar de ore invalid!!");
	if (d.get_teacher().size() == 0)
		msgs.push_back("Nume profesor vid!!");
	if (d.get_type().size() == 0 && d.get_type() != "curs" && d.get_type() != "seminar" && d.get_type() != "laborator")
		msgs.push_back("Tip invalid!!");

	if (msgs.size() > 0)
	{
		throw ValidateException(msgs);
	}
}

ostream& operator<<(ostream& out, const ValidateException& exp)
{
	for (const auto& msg : exp.msgs)
	{
		out << msg << "\n";
	}
	return out;
}

void test_validator()
{
	ValidateDisciplina val;
	Disciplina d{ "", "", "0", "", "" };
	try {
		val.validate(d);
	}
	catch (const ValidateException& exp) {
		std::stringstream sout;
		sout << exp;
		auto msj = sout.str();
		assert(msj.find("invalid") > 0);
		assert(msj.find("vid") > 0);
		assert(msj.find("vida") > 0);
	}

	Disciplina d2{ "51", "a", "1", "ora", "a" };
	try {
		val.validate(d2);
	}
	catch (const ValidateException& exp) {
		std::stringstream sout;
		sout << exp;
		auto msj = sout.str();
		assert(msj.find("invalid") > 0);
	}
}
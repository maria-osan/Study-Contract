#pragma once

#include "disciplina.h"

#include <string>
#include <vector>

using std::vector;
using std::string;
using std::ostream;

class ValidateDisciplina {

public:
	void validate(const Disciplina& d);
};

class ValidateException {
	vector<string> msgs;

public:
	ValidateException(const vector<string>& errors) : msgs{ errors } {}

	vector<string> get_msg() const
	{
		return msgs;
	}

	// friend function (I want to use private member msg)
	friend ostream& operator<<(ostream& out, const ValidateException& exp);
};

ostream& operator<<(ostream& out, const ValidateException& exp);

// ---TESTS---

void test_validator();
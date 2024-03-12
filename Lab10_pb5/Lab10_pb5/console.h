#pragma once

#include "service.h"
#include "disciplina.h"
#include "study_contract.h"

class Console {
	Service& srv;

	//study_contract& list;

	void study_contract_option();

	// Read data from the keyboard and add the new subject
	// throw exception if: it cannot be saved, it's not valid
	void add_UI();

	// Delete a subject from the vector of subjects
	// throw exception if the subject doesn't exist in the vector
	void delete_UI();

	// Search a subject in the vector
	// throw exception if the subject doesn't exist in the vector
	void search_UI();

	// print a list of subjects on the console
	void print(const vector<Disciplina>& d_lst);

public:
	Console(Service& srv) noexcept : srv{ srv } {}

	// does not allow copying objects
	Console(const Console& ot) = delete;

	void start();
};
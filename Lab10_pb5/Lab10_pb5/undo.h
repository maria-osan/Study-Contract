#pragma once

#include "disciplina.h"
#include "repository.h"


class Undo
{
public:
	virtual void do_undo() = 0;
	virtual ~Undo() = default;
};


class UndoAdd :public Undo
{
	Disciplina added_d;
	Repo& repo;

public:
	UndoAdd(Repo& r, const Disciplina& d) :repo{ r }, added_d{ d } {}
	void do_undo() override
	{
		repo.del(added_d);
	}
};

class UndoDelete :public Undo
{
	Disciplina deleted_d;
	Repo& repo;

public:
	UndoDelete(Repo& r, const Disciplina& d) :repo{ r }, deleted_d{ d } {}
	void do_undo() override
	{
		repo.store(deleted_d);
	}
};

class UndoModify :public Undo
{
	Disciplina modifyed_d;
	Repo& repo;
	string new_val;
	char what;

public:
	UndoModify(Repo& r, const Disciplina& d, const string& new_val, char what) :repo{ r }, modifyed_d{ d }, new_val{ new_val }, what{ what } {}
	void do_undo() override
	{
		repo.modify(modifyed_d, new_val, what);
	}
};
#pragma once

#include <QtWidgets>
#include <qmessagebox.h>
#include <qdebug.h>

#include <vector>
#include <string>

using std::vector;
using std::string;

#include "study_contract.h"
#include "repository.h"
#include "observer.h"
#include "TableModel.h"

class contractGUImodel :public QWidget, public Observer
{
private:
	study_contract& contr;
	Repo& repo;

	QLabel* lblMany = new QLabel("Cate:0");

	QTableView* tableV = new QTableView;
	TableModel* tableModel = new TableModel();
	//TableModel* tableModel = new TableModel(repo.get_all());

	/*QListWidget* lst = new QListWidget;
	QTableWidget* table = new QTableWidget{ 1, 5 };*/

	QPushButton* btnExit = new QPushButton{ "Iesire" };
	QPushButton* btnAddDis = new QPushButton{ "Adaugare" };
	QPushButton* btnEmpty = new QPushButton{ "Golire" };
	QPushButton* btnGenerate = new QPushButton{ "Generare" };
	QPushButton* btnExport = new QPushButton{ "Export" };

	QLineEdit* txtIdDis = new QLineEdit;
	QLineEdit* txtNumber = new QLineEdit;
	QLineEdit* txtFileName = new QLineEdit;

	void initGUIcmps();
	void connectSignalsSlots();
	void reloadList(const vector<Disciplina>& dis);

	void addDisContract();
	void emptyContract();
	void generateContract();
	void exportContract();

public:
	contractGUImodel(study_contract& c, Repo& r) : contr{ c }, repo{ r } {
		initGUIcmps();
		connectSignalsSlots();
		reloadList(contr.get_list());
	}

	void update() override
	{
		reloadList(contr.get_list());
	}

	~contractGUImodel()
	{
		contr.removeObserver(this);
	}
};
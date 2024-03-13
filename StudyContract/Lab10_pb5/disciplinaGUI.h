#pragma once

#include "disciplina.h"
#include "repository.h"
#include "service.h"
#include "contractGUI.h"
#include "observer.h"
#include "study_contract.h"
#include "contractGUImodel.h"

#include <QtWidgets>
#include <qmessagebox.h>
#include <qdebug.h>

#include <vector>
#include <string>

using std::vector;
using std::string;

class serviceGUI : public QWidget
{
private:
    Service& srv;
    Repo& repo;

    QListWidget* lst = new QListWidget;

    QPushButton* btnExit = new QPushButton{ "Iesire" };
    QPushButton* btnUndo = new QPushButton{ "Undo" };
    QPushButton* btnPrint = new QPushButton{ "Afisare" };
    QPushButton* btnAdd = new QPushButton{ "Adauga" };
    QPushButton* btnDelete = new QPushButton{ "Sterge" };
    QPushButton* btnModify = new QPushButton{ "Modifica" };

    QPushButton* btnSortName = new QPushButton{ "Sortare denumire" };
    QPushButton* btnSortHours = new QPushButton{ "Sortare nr ore" };
    QPushButton* btnSortTeacher = new QPushButton{ "Sortare profesori" };

    QPushButton* btnFilterHours = new QPushButton{ "Filtrare nr ore" };
    QPushButton* btnFilterTeacher = new QPushButton{ "Filtrare profesor" };

    QPushButton* btnContract = new QPushButton{ "Contract studiu" };
    QPushButton* btnContractRDOnly = new QPushButton{ "Contract studiu (read only)" };
    QPushButton* btnAddDis = new QPushButton{ "Adaugare" };
    QPushButton* btnEmpty = new QPushButton{ "Golire" };
    QPushButton* btnGenerate = new QPushButton{ "Generare" };
    QPushButton* btnExport = new QPushButton{ "Export" };

    QHBoxLayout* lyBtnDy = new QHBoxLayout;

    QGroupBox* groupBoxDisciplina = new QGroupBox{ "Disciplina:" };
    QGroupBox* groupBoxFilter = new QGroupBox{ "Filtrari:" };
    QGroupBox* groupBoxSort = new QGroupBox{ "Sortari:" };
    QGroupBox* groupBoxContract = new QGroupBox{ "Contract Studiu:" };

    QLineEdit* txtId = new QLineEdit;
    QLineEdit* txtName = new QLineEdit;
    QLineEdit* txtNrHours = new QLineEdit;
    QLineEdit* txtType = new QLineEdit;
    QLineEdit* txtTeacher = new QLineEdit;

    QLineEdit* txtfilterHours = new QLineEdit;
    QLineEdit* txtfilterTeacher = new QLineEdit;

    QLineEdit* txtIdDis = new QLineEdit;
    QLineEdit* txtNumber = new QLineEdit;
    QLineEdit* txtFileName = new QLineEdit;

    void initConnect();
    void reloadData(const std::vector<Disciplina>& dis);
    void initGUI();

    void addButtons(std::map<string, int> rap);
    void addDisciplina();
    void deleteDisciplina();
    void modifyDisciplina();
    void undo();
    void filterHours();
    void filterTeacher();
    void createContract();

public:
    serviceGUI(Service& srv, Repo& r) : srv { srv }, repo{ r }
    {
        initGUI();
        reloadData(srv.get_all());
        initConnect();
        addButtons(srv.raport());
    }
};
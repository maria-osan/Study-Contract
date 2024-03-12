#include "disciplinaGUI.h"

#include <QtWidgets>
#include <qmessagebox.h>
#include <qdebug.h>


void serviceGUI::initGUI()
{
    QHBoxLayout* lyMain = new QHBoxLayout{};
    setLayout(lyMain);

    // the left side: the list and the study contract
    auto stgLy = new QVBoxLayout;

    // adding the list
    stgLy->addWidget(lst);

    stgLy->addLayout(lyBtnDy);

    // adding the study contract layout
    auto lyContr = new QVBoxLayout;

    // add subject in the contract button
    auto ly_add = new QHBoxLayout;
    auto form_add = new QFormLayout;
    form_add->addRow("ID", txtIdDis);
    ly_add->addLayout(form_add);
    ly_add->addWidget(btnAddDis);
    lyContr->addLayout(ly_add);
    // generate contract button
    auto ly_generate = new QHBoxLayout;
    auto form_generate = new QFormLayout;
    form_generate->addRow("Numar discipline", txtNumber);
    ly_generate->addLayout(form_generate);
    ly_generate->addWidget(btnGenerate);
    lyContr->addLayout(ly_generate);
    // empty contract button
    lyContr->addWidget(btnEmpty);
    // export contract button
    auto ly_export = new QHBoxLayout;
    auto form_ecport = new QFormLayout;
    form_ecport->addRow("Nume fisier", txtFileName);
    ly_export->addLayout(form_ecport);
    ly_export->addWidget(btnExport);
    lyContr->addLayout(ly_export);
    //the contract buttons
    auto contract_btnLy = new QHBoxLayout;
    contract_btnLy->addWidget(btnContract);
    contract_btnLy->addWidget(btnContractRDOnly);
    lyContr->addLayout(contract_btnLy);

    groupBoxContract->setLayout(lyContr);
    stgLy->addWidget(groupBoxContract);

    lyMain->addLayout(stgLy);

    // the right side: the form for details, add/modify/delete/exit and filter/sort buttons
    auto drLy = new QVBoxLayout;

    // adding the form for details
    auto formLy = new QFormLayout;
    formLy->addRow("ID", txtId);
    formLy->addRow("Denumire", txtName);
    formLy->addRow("Nr ore", txtNrHours);
    formLy->addRow("Tip", txtType);
    formLy->addRow("Profesor", txtTeacher);
    groupBoxDisciplina->setLayout(formLy);
    drLy->addWidget(groupBoxDisciplina);

    // adding the buttons
    auto lyBtn = new QVBoxLayout;

    // adding the add, modify and delete buttons
    auto lyBtnAMD = new QHBoxLayout;
    lyBtnAMD->addWidget(btnAdd);
    lyBtnAMD->addWidget(btnModify);
    lyBtnAMD->addWidget(btnDelete);
    lyBtn->addLayout(lyBtnAMD);

    // adding the undo and print buttons
    auto lyBtnUndoPrint = new QHBoxLayout;
    lyBtnUndoPrint->addWidget(btnUndo);
    btnUndo->setEnabled(false);
    lyBtnUndoPrint->addWidget(btnPrint);
    lyBtn->addLayout(lyBtnUndoPrint);

    // adding the filter buttons
    auto filterLy = new QVBoxLayout;

    auto filterHoursLy = new QHBoxLayout;
    auto filterHoursForm = new QFormLayout;
    filterHoursForm->addRow("Nr ore", txtfilterHours);
    filterHoursLy->addLayout(filterHoursForm);
    filterHoursLy->addWidget(btnFilterHours);
    filterLy->addLayout(filterHoursLy);

    auto filterTeacherLy = new QHBoxLayout;
    auto filterTeacherForm = new QFormLayout;
    filterTeacherForm->addRow("Profesor", txtfilterTeacher);
    filterTeacherLy->addLayout(filterTeacherForm);
    filterTeacherLy->addWidget(btnFilterTeacher);
    filterLy->addLayout(filterTeacherLy);

    groupBoxFilter->setLayout(filterLy);
    lyBtn->addWidget(groupBoxFilter);

    // adding the sort buttons
    QHBoxLayout* lyBtnSort = new QHBoxLayout;
    lyBtnSort->addWidget(btnSortName);
    lyBtnSort->addWidget(btnSortHours);
    lyBtnSort->addWidget(btnSortTeacher);
    groupBoxSort->setLayout(lyBtnSort);
    lyBtn->addWidget(groupBoxSort);

    // adding the exit button
    lyBtn->addWidget(btnExit);

    drLy->addLayout(lyBtn);
    lyMain->addLayout(drLy);
}

void serviceGUI::initConnect()
{
    QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
        auto sel = lst->selectedItems();
        if (sel.isEmpty())
        {
            txtId->setText("");
            txtName->setText("");
            txtNrHours->setText("");
            txtType->setText("");
            txtTeacher->setText("");
        }
        else
        {
            auto selItem = sel.at(0);
            auto text = selItem->text().toStdString();
            std::string id;
            id.assign(text, 2, 4);
            //qDebug() << id << "\n";
            txtId->setText(QString::fromStdString(id));
            auto d = srv.find(id);
            txtName->setText(QString::fromStdString(d.get_name()));
            txtNrHours->setText(QString::fromStdString(d.get_nr_hours()));
            txtType->setText(QString::fromStdString(d.get_type()));
            txtTeacher->setText(QString::fromStdString(d.get_teacher()));
        }
        });

    // print button
    QObject::connect(btnPrint, &QPushButton::clicked, [&]() {
        reloadData(srv.get_all());
        });

    // undo button
    QObject::connect(btnUndo, &QPushButton::clicked, this, &serviceGUI::undo);

    // contract button
    QObject::connect(btnContract, &QPushButton::clicked, this, &serviceGUI::createContract);

    // contract read only button
    QObject::connect(btnContractRDOnly, &QPushButton::clicked, [&]() {
        contractReadOnlyGUI* contr_gui = new contractReadOnlyGUI{ srv.getContract() };
        contr_gui->show();
        });

    // add a subject in the study contract button
    QObject::connect(btnAddDis, &QPushButton::clicked, [&]() {
        try {
            srv.addStudyContract(txtIdDis->text().toStdString());
            txtIdDis->clear();
        }
        catch (RepoException& ex) {
            QMessageBox::warning(this, "Warning!", QString::fromStdString(ex.get_msg()));
        }
        });

    // generate study contract button
    QObject::connect(btnGenerate, &QPushButton::clicked, [&]() {
        srv.addRandom(txtNumber->text().toInt());
        txtNumber->clear();
        });

    // empty study contract button
    QObject::connect(btnEmpty, &QPushButton::clicked, [&]() {
        srv.emptyStudyContract();
        });

    // export study contract button
    QObject::connect(btnExport, &QPushButton::clicked, [&]() {
        srv.exportContractHTML(txtFileName->text().toStdString());
        txtFileName->clear();
        });

    // sort by subject name button
    QObject::connect(btnSortName, &QPushButton::clicked, [&]() {
        qDebug() << "we are here!!";
        reloadData(srv.sort_name());
        });

    // sort by number of hours button
    QObject::connect(btnSortHours, &QPushButton::clicked, [&]() {
        qDebug() << "we are here!!";
        reloadData(srv.sort_hours());
        });

    // sort by teacher button
    QObject::connect(btnSortTeacher, &QPushButton::clicked, [&]() {
        qDebug() << "we are here!!";
        reloadData(srv.sort_teacher_type());
        });

    // add button
    QObject::connect(btnAdd, &QPushButton::clicked, this, &serviceGUI::addDisciplina);

    // modify button
    QObject::connect(btnModify, &QPushButton::clicked, this, &serviceGUI::modifyDisciplina);

    // delete button
    QObject::connect(btnDelete, &QPushButton::clicked, this, &serviceGUI::deleteDisciplina);

    /// filter buttons
    QObject::connect(btnFilterHours, &QPushButton::clicked, this, &serviceGUI::filterHours);
    QObject::connect(btnFilterTeacher, &QPushButton::clicked, this, &serviceGUI::filterTeacher);

    // exit button
    QObject::connect(btnExit, &QPushButton::clicked, [&]() {
        qDebug() << "Exit button pressed!!";
        //QMessageBox::information(nullptr, "Info", "Exit button pressed!!");
        close();
        });
}

void serviceGUI::reloadData(const std::vector<Disciplina>& dis)
{
    lst->clear();

    txtId->clear();
    txtName->clear();
    txtNrHours->clear();
    txtType->clear();
    txtTeacher->clear();
    txtfilterHours->clear();
    txtfilterTeacher->clear();

    for (const auto& d : dis)
    {
        lst->addItem("- " + QString::fromStdString(d.get_id()) + ": " + QString::fromStdString(d.get_name()) + ", " + QString::fromStdString(d.get_type()) + " ( " + QString::fromStdString(d.get_nr_hours()) + " ore/sapt ), " + QString::fromStdString(d.get_teacher()));
    }
}

void serviceGUI::addButtons(std::map<string, int> rap)
{
    for (const auto& r : rap)
    {
        auto btn = new QPushButton{ QString::fromStdString(r.first) };
        lyBtnDy->addWidget(btn);
        QObject::connect(btn, &QPushButton::clicked, [this, btn, r]() {
            QMessageBox::information(nullptr, "Info", QString::number(r.second));
            delete btn;
            });
    }
}

void serviceGUI::addDisciplina()
{
    try {
        srv.add(txtId->text().toStdString(), txtName->text().toStdString(), txtNrHours->text().toStdString(), txtType->text().toStdString(), txtTeacher->text().toStdString());
        for (const auto d : srv.get_all())
            qDebug() << d.get_name() << "\n";
        reloadData(srv.get_all());
        btnUndo->setEnabled(true);
    }
    catch (RepoException& ex) {
        QMessageBox::warning(this, "Warning!", QString::fromStdString(ex.get_msg()));
    }
    catch (ValidateException& exps) {
        for (auto e : exps.get_msg())
            QMessageBox::warning(this, "Warning!", QString::fromStdString(e));
    }
}

void serviceGUI::deleteDisciplina()
{
    try {
        srv.del(txtId->text().toStdString());
        reloadData(srv.get_all());
        btnUndo->setEnabled(true);
    }
    catch (RepoException& ex) {
        QMessageBox::warning(this, "Warning!", QString::fromStdString(ex.get_msg()));
    }
}

void serviceGUI::modifyDisciplina()
{
    try {
        auto d = srv.find(txtId->text().toStdString());
        if (txtName->text().toStdString() != "")
            srv.modify(d, txtName->text().toStdString(), '1');
        if(txtNrHours->text().toStdString() != "")
            srv.modify(d, txtNrHours->text().toStdString(), '2');
        if (txtType->text().toStdString() != "")
            srv.modify(d, txtType->text().toStdString(), '3');
        if (txtTeacher->text().toStdString() != "")
            srv.modify(d, txtTeacher->text().toStdString(), '4');
        reloadData(srv.get_all());
        btnUndo->setEnabled(true);
    }
    catch (RepoException& ex) {
        QMessageBox::warning(this, "Warning!", QString::fromStdString(ex.get_msg()));
    }
}

void serviceGUI::filterHours()
{
    auto filterd = srv.filter_equal_hours(txtfilterHours->text().toStdString());
    reloadData(filterd);
}

void serviceGUI::filterTeacher()
{
    auto filterd = srv.filter_same_teacher(txtfilterTeacher->text().toStdString());
    reloadData(filterd);
}

void serviceGUI::undo()
{
    try {
        srv.undo();
        reloadData(srv.get_all());
    }
    catch (RepoException& ex) {
        QMessageBox::warning(this, "Warning!", QString::fromStdString(ex.get_msg()));
        btnUndo->setEnabled(false);
    }
}

void serviceGUI::createContract()
{
    /*contractGUI* contrGUI = new contractGUI{ srv.getContract(), repo };
    contrGUI->show();*/

    contractGUImodel* contrGUI = new contractGUImodel{ srv.getContract(), repo };
    contrGUI->show();
}
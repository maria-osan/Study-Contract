#include "contractGUI.h"

#include <qtimer.h>

void contractGUI::initGUIcmps()
{
	QHBoxLayout* ly_main = new QHBoxLayout;
	setLayout(ly_main);

	// table header
	QStringList tabelHeader;
	tabelHeader << "ID" << "NUME" << "TIP" << "NR ORE" << "PROFESOR";
	this->table->setHorizontalHeaderLabels(tabelHeader);

	// resize the table according to the content
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	ly_main->addWidget(table);

	// the list of subjects from the study contract
	//ly_main->addWidget(lst);

	auto ly_btn = new QVBoxLayout;
	
	// add button
	auto ly_add = new QHBoxLayout;
	auto form_add = new QFormLayout;
	form_add->addRow("ID", txtIdDis);
	ly_add->addLayout(form_add);
	ly_add->addWidget(btnAddDis);
	ly_btn->addLayout(ly_add);

	// generate button
	auto ly_generate = new QHBoxLayout;
	auto form_generate = new QFormLayout;
	form_generate->addRow("Numar discipline", txtNumber);
	ly_generate->addLayout(form_generate);
	ly_generate->addWidget(btnGenerate);
	ly_btn->addLayout(ly_generate);

	// empty button
	ly_btn->addWidget(btnEmpty);

	// export button
	/*auto ly_export = new QHBoxLayout;
	auto form_ecport = new QFormLayout;
	form_ecport->addRow("Nume fisier", txtFileName);
	ly_export->addLayout(form_ecport);
	ly_export->addWidget(btnExport);
	ly_btn->addLayout(ly_export);*/

	// exit button
	//ly_btn->addWidget(btnExit);

	ly_main->addLayout(ly_btn);

	
}

void contractGUI::connectSignalsSlots()
{
	contr.addObserver(this);

	// add button
	QObject::connect(btnAddDis, &QPushButton::clicked, this, &contractGUI::addDisContract);

	// generate button
	QObject::connect(btnGenerate, &QPushButton::clicked, this, &contractGUI::generateContract);

	// epmty button
	QObject::connect(btnEmpty, &QPushButton::clicked, this, &contractGUI::emptyContract);

	// export button
	QObject::connect(btnExport, &QPushButton::clicked, this, &contractGUI::exportContract);

	// exit button
	QObject::connect(btnExit, &QPushButton::clicked, [&]() {
		qDebug() << "Exit button pressed!!";
		close();
		});
}

void contractGUI::reloadList(const vector<Disciplina>& dis)
{
	//lst->clear();
	table->clearContents();
	table->setRowCount(dis.size());

	txtIdDis->setText("");
	txtNumber->setText("");
	txtFileName->setText("");

	int nrLine = 0;
	for (const auto& d : dis)
	{
		table->setItem(nrLine, 0, new QTableWidgetItem(QString::fromStdString(d.get_id())));
		table->setItem(nrLine, 1, new QTableWidgetItem(QString::fromStdString(d.get_name())));
		table->setItem(nrLine, 2, new QTableWidgetItem(QString::fromStdString(d.get_type())));
		table->setItem(nrLine, 3, new QTableWidgetItem(QString::fromStdString(d.get_nr_hours())));
		table->setItem(nrLine, 4, new QTableWidgetItem(QString::fromStdString(d.get_teacher())));
		nrLine++;
		//lst->addItem("- " + QString::fromStdString(d.get_id()) + ": " + QString::fromStdString(d.get_name()) + ", " + QString::fromStdString(d.get_type()) + " ( " + QString::fromStdString(d.get_nr_hours()) + " ore/sapt ), " + QString::fromStdString(d.get_teacher()));
	}
}

void contractGUI::addDisContract()
{
	try {
		auto d = repo.find(txtIdDis->text().toStdString());
		contr.add(d);
		reloadList(contr.get_list());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning!", QString::fromStdString(ex.get_msg()));
	}
}

void contractGUI::generateContract()
{
	int nr = txtNumber->text().toInt();
	auto all = repo.get_all();
	contr.generate(nr, all);
	reloadList(contr.get_list());
}

void contractGUI::emptyContract()
{
	contr.empty_list();
	reloadList(contr.get_list());
}

void contractGUI::exportContract()
{
	auto f_name = txtFileName->text().toStdString();
	string out = contr.export_html(f_name);
	if (out == "")
		reloadList(contr.get_list());
}
#include "contractGUImodel.h"
#include "disciplina.h"

#include <QtWidgets>
#include <qtimer.h>

void contractGUImodel::initGUIcmps()
{
	QHBoxLayout* ly_main = new QHBoxLayout;
	setLayout(ly_main);

	//the left side: the table and the count label
	QWidget* widLeft = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	widLeft->setLayout(vl);

	vl->addWidget(lblMany);

	tableV = new QTableView;
	vl->addWidget(tableV);
	tableModel->setDiscipline(repo.get_all());
	tableV->setModel(tableModel);

	widLeft->setLayout(vl);
	ly_main->addWidget(widLeft);
	
	// ----
	//// table header
	//QStringList tabelHeader;
	//tabelHeader << "ID" << "NUME" << "TIP" << "NR ORE" << "PROFESOR";
	//this->table->setHorizontalHeaderLabels(tabelHeader);

	//// resize the table according to the content
	//table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	//ly_main->addWidget(table);
	// ----

	// the right side: buttons
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

void contractGUImodel::connectSignalsSlots()
{
	contr.addObserver(this);

	// add button
	QObject::connect(btnAddDis, &QPushButton::clicked, this, &contractGUImodel::addDisContract);

	// generate button
	QObject::connect(btnGenerate, &QPushButton::clicked, this, &contractGUImodel::generateContract);

	// epmty button
	QObject::connect(btnEmpty, &QPushButton::clicked, this, &contractGUImodel::emptyContract);

	// export button
	QObject::connect(btnExport, &QPushButton::clicked, this, &contractGUImodel::exportContract);

	// exit button
	QObject::connect(btnExit, &QPushButton::clicked, [&]() {
		qDebug() << "Exit button pressed!!";
		close();
		});
}

void contractGUImodel::reloadList(const vector<Disciplina>& dis)
{
	txtIdDis->clear();
	txtNumber->clear();
	txtFileName->clear();

	lblMany->setText(QString{ "Cate: " } + QString::number(dis.size()));
	tableModel->setDiscipline(dis);
}

void contractGUImodel::addDisContract()
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

void contractGUImodel::generateContract()
{
	int nr = txtNumber->text().toInt();
	auto all = repo.get_all();
	contr.generate(nr, all);
	reloadList(contr.get_list());
}

void contractGUImodel::emptyContract()
{
	contr.empty_list();
	reloadList(contr.get_list());
}

void contractGUImodel::exportContract()
{
	auto f_name = txtFileName->text().toStdString();
	string out = contr.export_html(f_name);
	if (out == "")
		reloadList(contr.get_list());
}
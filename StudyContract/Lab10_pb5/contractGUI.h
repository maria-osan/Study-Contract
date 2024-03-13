#pragma once

#include <QtWidgets/qwidget.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
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

class contractGUI :public QWidget, public Observer
{
private:
	study_contract& contr;
	Repo& repo;

	QListWidget* lst = new QListWidget;
	QTableWidget* table = new QTableWidget{ 1, 5 };

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
	contractGUI(study_contract& c, Repo& r) : contr{ c }, repo{ r } {
		initGUIcmps();
		connectSignalsSlots();
		reloadList(contr.get_list());
		setAttribute(Qt::WA_DeleteOnClose); //daca vreau sa se distruga fereastra imediat dupa inchidere
	}

	void update() override
	{
		reloadList(contr.get_list());
	}

	~contractGUI()
	{
		contr.removeObserver(this);
	}
};


class contractReadOnlyGUI :public QLabel, public Observer
{
private:
	study_contract& contr;

	QListWidget* lst;

public:
	contractReadOnlyGUI(study_contract& contr) :contr{ contr } 
	{
		/*setFont(QFont{ "arial",24 });
		setAttribute(Qt::WA_DeleteOnClose);*/ //daca vreau sa se distruga fereastra imediat dupa inchidere
		contr.addObserver(this);
		//update();
	}

	void bulid()
	{
		lst = new QListWidget;
		QHBoxLayout* mainLy = new QHBoxLayout;
		mainLy->addWidget(lst);
		this->setLayout(mainLy);
	}

	void update() override {
		//setText("Cosul contine:" + QString::number(contr.get_list().size()));
		this->repaint();
	}

	void reloadList()
	{
		lst->clear();
		for (auto elem : contr.get_list())
			lst->addItem(QString::fromStdString(elem.get_name()));
	}

	void paintEvent(QPaintEvent* ev) override
	{
		QPainter p(this);

		p.drawImage(0, 0, QImage("floare.jpg"));
		srand(time(0));

		int x = -20;
		for (auto elem : contr.get_list())
		{
			x += 40;
			int forma = rand() % 4;
			int inaltime = rand() % 130;
			int start_y = rand() % 60;
			QColor color;

			int color_num = rand() % 10;
			switch (color_num)
			{
			case 0:
				color = Qt::red;
				break;
			case 1:
				color = Qt::green;
				break;
			case 2:
				color = Qt::black;
				break;
			case 3:
				color = Qt::blue;
				break;
			case 4:
				color = Qt::lightGray;
				break;
			case 5:
				color = Qt::yellow;
				break;
			case 6:
				color = Qt::cyan;
				break;
			case 7:
				color = Qt::magenta;
				break;
			case 8:
				color = Qt::darkGreen;
				break;
			case 9:
				color = Qt::darkBlue;
				break;
			default:
				break;
			}

			switch (forma)
			{
			case 0: // dreptunghi
				p.drawRect(x, start_y, 20, inaltime);
				break;
			case 1: // elipsa
				p.drawEllipse(x, start_y, 20, inaltime);
				break;
			case 2: // dreptunghi colorat
				p.fillRect(x, start_y, 20, inaltime, color);
				break;
			default: // dreptunghi colorat
				p.fillRect(x, start_y, 20, inaltime, color);
				break;
			}
		}
	}

	~contractReadOnlyGUI() {
		contr.removeObserver(this);
	}
};
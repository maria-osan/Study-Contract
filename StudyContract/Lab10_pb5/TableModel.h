#pragma once

#include "disciplina.h"
#include "service.h"

#include <QAbstractTableModel>
#include <qdebug.h>
#include <vector>

class TableModel :public QAbstractTableModel
{
	vector<Disciplina> list;

public:
	TableModel() {}

	TableModel(const vector<Disciplina>& lst) :list{ lst } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return list.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return 5;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override
	{
		if (role == Qt::DisplayRole)
		{
			qDebug() << "row:" << index.row()<< " col:" << index.column();
			Disciplina d = list[index.row()];
			if (index.column() == 0)
			{
				return QString::fromStdString(d.get_id());
			}
			else if (index.column() == 1)
			{
				return QString::fromStdString(d.get_name());
			}
			else if (index.column() == 2)
			{
				return QString::fromStdString(d.get_nr_hours());
			}
			else if (index.column() == 3)
			{
				return QString::fromStdString(d.get_type());
			}
			else if (index.column() == 4)
			{
				return QString::fromStdString(d.get_teacher());
			}
		}
		return QVariant{};
	}

	Disciplina getDisciplina(const QModelIndex& index)
	{
		return list[index.row()];
	}

	void setDiscipline(const vector<Disciplina>& lst)
	{
		this->list = lst;
		QModelIndex topLeft = createIndex(0, 0);
		QModelIndex bottomRight = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomRight);
		emit layoutChanged();
	}
};
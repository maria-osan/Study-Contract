#pragma once

#include "disciplina.h"
#include "repository.h"
#include "service.h"

#include <QAbstractListModel>
#include <qdebug.h>
#include <vector>

class ListModel :public QAbstractListModel 
{
	vector<Disciplina> list;

public:
	ListModel() {}

	ListModel(const vector<Disciplina>& lst) :list{ lst } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return list.size();
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override
	{
		if (role == Qt::DisplayRole)
		{
			qDebug() << "get row:" << index.row();			
			auto id = list[index.row()].get_id();
			return QString::fromStdString(id);
		}
		if (role == Qt::UserRole)
		{
			auto name = list[index.row()].get_name();
			return QString::fromStdString(name);
		}
		return QVariant{};
	}
};
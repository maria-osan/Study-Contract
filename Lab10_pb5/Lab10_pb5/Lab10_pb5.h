#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab10_pb5.h"

class Lab10_pb5 : public QMainWindow
{
    Q_OBJECT

public:
    Lab10_pb5(QWidget *parent = nullptr);
    ~Lab10_pb5();

private:
    Ui::Lab10_pb5Class ui;
};

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TPFour.h"
#include <Windows.h>
#include "Dask64.h"
#include <QTimer>


class TPFour : public QMainWindow
{
    Q_OBJECT

public:
    TPFour(QWidget *parent = Q_NULLPTR);
	void issue(int value1, int value2);

public slots :
	void fourOn();
	void fourOff();
	void pourcent();
	void timerOn();
	void timerOff();
	void getTemp();
	
private:
    Ui::TPFourClass ui;
	I16 card;
	double tension;
	float temp;
	QTimer *timer;
};

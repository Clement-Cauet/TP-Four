//*********************************************************************************************
//* Programme : TPFour.cpp								Date : 07/12/2021
//*														Dernière MAJ : 07/12/2021
//*--------------------------------------------------------------------------------------------
//*Programmeurs :	BOUCHER Louis							Classe : BTSSN2
//*					CAUET Clément
//*					LARIDANT Julien
//*--------------------------------------------------------------------------------------------
//*
//* BUT : Commander l'activation d'un four industriel
//*
//*********************************************************************************************

#include "TPFour.h"
#include <qdebug.h>

TPFour::TPFour(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	card = Register_Card(PCI_9111DG, 0);

	ui.buttonOff->setEnabled(false);
	ui.puissance->setEnabled(false);

	ui.puissance->setValue(0);
}

/* Allume le four et initialise les valeurs */
void TPFour::fourOn()
{
	ui.buttonOn->setEnabled(false);
	ui.buttonOff->setEnabled(true);
	ui.puissance->setEnabled(true);

	ui.pourcent->setText(QString::number(ui.puissance->value()) + " %");

	timerOn();

	issue(0, 0);
}

/* Eteint le four et reset les valeurs */
void TPFour::fourOff()
{
	ui.buttonOn->setEnabled(true);
	ui.buttonOff->setEnabled(false);
	ui.puissance->setEnabled(false);

	ui.puissance->setValue(0);

	timerOff();

	issue(0, 0);
}

/* Récupère les valeurs du slider */
void TPFour::pourcent()
{
	ui.pourcent->setText(QString::number(ui.puissance->value()) + " %");

	issue(0, ui.puissance->value());
}

/* Démarrage de l'échantillonnage */
void TPFour::timerOn()
{
	timer = new QTimer(this);
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(getTemp()));

	timer->start(3000);
}

/* Coupure du timer */
void TPFour::timerOff()
{
	QObject::disconnect(timer, SIGNAL(timeout()), this, SLOT(getTemp()));
}

/* Envoie les informations à la cartes 9111 */
void TPFour::issue(int value1, int value2)
{
	if (value2 > 0) {
		value2 /= 10;
	}

	AO_VWriteChannel(card, value1, value2);
}

/* Convertion de la tension en degré celsuis */
void TPFour::getTemp()
{
	AI_VReadChannel(card, 0, AD_B_10_V, &tension);

	temp = (51 * tension) - 73;

	ui.temp->setText(QString::number(temp) + " °C");
}

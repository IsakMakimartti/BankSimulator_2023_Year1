#include "creditdebit.h"
#include "ui_creditdebit.h"
#include <QDebug>
CreditDebit::CreditDebit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditDebit)
{
    setWindowTitle("Valitse Tili");
    ui->setupUi(this);
    connect(ui->Push_Credit,SIGNAL(clicked(bool)),this,SLOT(valinta()));
    connect(ui->Push_Debit,SIGNAL(clicked(bool)),this,SLOT(valinta()));
}

CreditDebit::~CreditDebit()
{
    delete ui;
}

void CreditDebit::valinta()
{
    setWindowTitle("Valitse Tili");
    QPushButton * sent = qobject_cast<QPushButton*>(sender());
    QString name = sent -> objectName();
    //Katsotaan lähettäjän nimi ja sitä kayttäen asetetaan boolean muutuja Debit sekä lähetetään signaali joka kertoo ikkunan sammuneen
    if(name == "Push_Debit"){
        CreditDebitIkkuna = true;
        Debit = true;
        emit sulkuu();
    } else {
        CreditDebitIkkuna = true;
        Debit = false;
        emit sulkuu();
    }
    this->close();
    this->deleteLater();
}




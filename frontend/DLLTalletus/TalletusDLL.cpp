#include "TalletusDLL.h"
#include "ui_TalletusDLL.h"
#include <QDebug>

Talletus::Talletus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Talletus)
{    
    qDebug()<<"DLL:n konstruktorissa";

    ui->setupUi(this);

    setWindowTitle("Talletus");

    //Rajataan luku 1 ja 9999 välille.
    validator = new QIntValidator(1, 9999, this);
    ui->textSumma->setValidator(validator);

    //Laitetaan napit toimimaan.
    connect(ui->buttonEnter, SIGNAL(clicked()),
            this, SLOT(clickHandlerEnter()));
    connect(ui->peruutaButton, SIGNAL(clicked()),
            this, SLOT(clickHandlerEdellinen()));
}

Talletus::~Talletus()
{    
    qDebug()<<"DLL:n desktruktorissa";
    delete ui;
}

void Talletus::clickHandlerEnter()
{
    float debitSaldo, creditSaldo;
    qDebug()<<"Debitsaldo: " + DebitSaldo;
    qDebug()<<"Creditsald0 : " + CreditSaldo;
    qDebug()<<Debit;
    qDebug()<<"DLL:n clickHandlerEnter";

    debitSaldo = DebitSaldo.toFloat();
    creditSaldo = CreditSaldo.toFloat();
    qDebug()<<ui->textSumma->text().toFloat();
    lahetettavaLuku = ui->textSumma->text().toFloat();
    qDebug()<<"testi";
    qDebug()<<lahetettavaLuku;

    //Tarkistetaan täsmääkö ehto. Lähetetään talletettu luku emitillä jos täsmää ja suljetaan ikkuna.
    if(Debit == true) {
        emit lahetys(debitSaldo, lahetettavaLuku);
        ui->textSumma->clear();
        this->close();
    }

    //Tarkistetaan täsmääkö ehto. Lähetetään talletettu luku emitillä jos täsmää ja suljetaan ikkuna.
    else if(Debit == false) {
        emit lahetys(creditSaldo, lahetettavaLuku);
        ui->textSumma->clear();
        this->close();
    }
}

void Talletus::clickHandlerEdellinen()
{
    this->close();
}

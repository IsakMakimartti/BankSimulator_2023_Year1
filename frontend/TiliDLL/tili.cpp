#include "tili.h"
#include "ui_tili.h"
#include <QDebug>
Tili::Tili(QWidget *parent):
    QDialog(parent),
    ui(new Ui::Tili)
{

    ui->setupUi(this);
    ui->Huomautus->setVisible(false);
    setWindowTitle("Valikko");
    connect(ui->pushValinta, SIGNAL(clicked(bool)),
            this, SLOT(clickHandlerTilinValinta()));
    connect(ui->pushKirjauduUlos, SIGNAL(clicked(bool)),
            this, SLOT(clickHandlerKirjauduUlos()));
    connect(ui->pushHistoria, SIGNAL(clicked(bool)),
            this, SLOT(clickHandlerHistoria()));
    connect(ui->pushTalletusNosto, SIGNAL(clicked(bool)),
            this, SLOT(clickHandlerTalletus()));
    connect(ui->Push_Nosto, SIGNAL(clicked(bool)),this,SLOT(clickHandlerNosto()));

    timeStart();
}

Tili::~Tili()
{
    delete ui;
}

void Tili::TiliNumSet()
{
    qDebug()<<"tilinumset";
    qDebug()<<Tilinum;
    ui->Lable_TiliNumero->setText(Tilinum);
    if(Debit==true){
        ui->Lable_Otsikko->setText("Debit");
        ui->label_saldo->setText(DebitSaldo+"€");
    } else {
        ui->Lable_Otsikko->setText("Credit");
        ui->label_saldo->setText(CreditSaldo+"€");
    }
}
void Tili::clickHandlerTilinValinta()
{
    qDebug()<<"Tilin valinta";
    qDebug()<<Valinta;
    if(Valinta==false){
    ui->Huomautus->setVisible(true);
    }else {
        emit creditDebit();
        timeStart();
    }
}

void Tili::clickHandlerKirjauduUlos()
{
    qDebug()<<"KirjauduUlos";
    ui->Huomautus->setVisible(false);
    emit kirjauduUlos();
}

void Tili::clickHandlerNosto()
{
    qDebug()<<"Nosto";
     ui->Huomautus->setVisible(false);
    emit nosto();
     timeStart();

}

void Tili::clickHandlerTalletus()
{
    qDebug()<<"Talletus";
     ui->Huomautus->setVisible(false);
    emit talletus();
     timeStart();
}

void Tili::Tilifinished(QNetworkReply *reply)
{
    response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString IdTili,Creditsal,Debitsal;
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        IdTili+=QString::number(json_obj["idTili"].toInt());
        Debitsal+=QString::number(json_obj["DebitSaldo"].toDouble());
        Creditsal+=QString::number(json_obj["CreditSaldo"].toDouble());
    }
    qDebug()<<Debitsal;
    qDebug()<<Creditsal;
    CreditSaldo = Creditsal;
    DebitSaldo = Debitsal;

    TiliNumSet();
}

void Tili::TimeOut()
{
    qDebug()<<"QTimeOut";
    aika.stop();
    emit kirjauduUlos();
    aika.disconnect();
}

void Tili::timeStart()
{
    aika.stop();
    aika.disconnect();
    aika.start(20000);
    connect(&aika,SIGNAL(timeout()),
            this,SLOT(TimeOut()));
}

void Tili::tilihaku()
{
    qDebug()<<"Tilin id: " + Tiliid;
    QNetworkRequest request(("http://localhost:3000/tili/" + Tiliid));
    request.setRawHeader(QByteArray("Authorization"),(token));
    tiliptr = new QNetworkAccessManager(this);
    connect(tiliptr, SIGNAL(finished (QNetworkReply*)), this, SLOT(Tilifinished(QNetworkReply*)));
    reply = tiliptr->get(request);
}

void Tili::clickHandlerHistoria()
{
    qDebug()<<"Historia";
     ui->Huomautus->setVisible(false);
    emit historia();
     timeStart();
}

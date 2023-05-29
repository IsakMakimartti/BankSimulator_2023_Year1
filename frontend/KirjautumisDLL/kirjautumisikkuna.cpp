#include "kirjautumisikkuna.h"
#include "ui_kirjautumisikkuna.h"
#include <QDebug>
#include <QString>
#include <QFrame>
Kirjautumisikkuna::Kirjautumisikkuna(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Kirjautumisikkuna)
{
    ui->setupUi(this);
    //asetetaan nimi uille
    setWindowTitle("Kirjaudu sisaan");
    creditptr = new CreditDebit;
    connect(ui->Push_Peruuta,SIGNAL(clicked(bool)), this, SLOT(sulku()));
    //tehdään yhteys signaaliin joka tulee silloin kun creditdebit ikkuna sammuu
    connect(creditptr,SIGNAL(sulkuu()),this,SLOT(sulku()));
}

Kirjautumisikkuna::~Kirjautumisikkuna()
{
    delete ui;
}

const QByteArray &Kirjautumisikkuna::getToken() const
{
    return token;
}

void Kirjautumisikkuna::setToken(const QByteArray &newToken)
{
    token = newToken;
}
void Kirjautumisikkuna::pinkoodi()
{
    //verrataan Rest Apilta saatua responsea
    if(response_data!="false"){
        //asetetaan UI:hin pieni viesti asiakkaalle
        ui->Lable_viesti->setText("Pinkoodi on oikein");
        pinauth = true;
        //avataan credit debit valikko
        QString key = DatabaseKey;
        tilinhaku("/kortti/" + key);
    } else {
        ui->Lable_viesti->setText("Pinkoodi on vaarin");
        //vähennetään asiakkaalta Yksi yritys kolmesta jos pin koodi on väärin ja asetetaan se Ui:hin
        yritys--;
        QString YritysUI = QString::number(yritys);
        ui->Lable_Yritys->setText("Yrityksiä jäljellä: " + YritysUI);
        ui->Lable_Yritys->setStyleSheet("background-color: rgba(255,51,51,0.6); font-weight: 600");
    }
    //suljetaan ikkuna jos asiakas ei anna oikeaa pinkoodia 3ssa yrityksessä
    if(yritys==0){
        this->deleteLater();
        this->close();
    }
}
void Kirjautumisikkuna::tilinhaku(QString a)
{
    //qDebug()<<a;
    QNetworkRequest request((URL + a));
    request.setRawHeader(QByteArray("Authorization"),(token));
    loginptr = new QNetworkAccessManager(this);
    connect(loginptr, SIGNAL(finished (QNetworkReply*)), this, SLOT(Tilifinished(QNetworkReply*)));
    reply = loginptr->get(request);
}

void Kirjautumisikkuna::pinkoodiGET(QNetworkReply*)
{
    //luetaan Backendiltä saatu vastaus ja tarkistetaan se tässä sekä Pinkoodi funktiossa. Poistetaan saadut vastaukset
    response_data=reply->readAll();
    if(QString::compare(response_data,"-4078")==0 || response_data.length()==0){
           ui->Lable_viesti->setText("Ongelma Yhteydessä");
    }
    if(response_data != "false"){
        this->setToken("Bearer " + response_data);
     }
    pinkoodi();
    }
void Kirjautumisikkuna::sulku()
{
 //haetaan asiakkaan valinta
    qDebug()<<"Tiliid " + TilinId;
 if(creditptr->CreditDebitIkkuna == true){
 debit = creditptr->Debit;
 }
 qDebug()<<"DebitMuutuja: ";
 qDebug()<<debit;
 //lähetetään mainwindowiin signaali
 emit sulkeutuu();
 creditptr->close();
 creditptr->deleteLater();
 this->deleteLater();
 this->close();
}
void Kirjautumisikkuna::on_Push_Kirjaudu_clicked()
{
 //Kirjaudu nappia painaessa verrataan annettua Pinkoodia database Pinkoodiin. Lähetetään tiedot Backendin puolelle jossa annettu pinniä verrataan Hashed pinkoodiin CryptJS:sän avulla
 QString pinkoodi = ui->Line_Input->text();
 QJsonObject Objptr;
 loginptr = new QNetworkAccessManager(this);
 //asetetaan lähetettävät muutujat
 Objptr.insert("idKortti",DatabaseKey);
 Objptr.insert("pinkoodi",pinkoodi);
 //asetetaan osoite
 QNetworkRequest req((URL + "/login"));
 req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
 connect(loginptr, SIGNAL(finished (QNetworkReply*)), this, SLOT(pinkoodiGET(QNetworkReply*)));
 reply = loginptr->post(req, QJsonDocument(Objptr).toJson());
}

void Kirjautumisikkuna::Tilifinished(QNetworkReply *reply)
{
    response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString CreditNum,DebitNum, IdTili,IdAsiakas,Creditsal,Debitsal;
    foreach (const QJsonValue &value, json_array) {
       QJsonObject json_obj = value.toObject();
       IdTili+=QString::number(json_obj["idTili"].toInt());
       IdAsiakas+=QString::number(json_obj["idAsiakas"].toInt());
       CreditNum+=QString(json_obj["CreditTilinumero"].toString());
       DebitNum+=QString(json_obj["DebitTilinumero"].toString());
       Debitsal+=QString::number(json_obj["DebitSaldo"].toDouble());
       Creditsal+=QString::number(json_obj["CreditSaldo"].toDouble());
    }
    qDebug()<<"IdTili:" + IdTili;
    qDebug()<<"Yksi Kierros";
    if (CreditNum == "" && DebitNum == ""){
    asiakasID = IdAsiakas;
    TilinId = IdTili;
    tilinhaku("/tili/" + IdTili);
    } else {
    Creditsaldo = Creditsal;
    Debitsaldo = Debitsal;
    CreditTiliNum = CreditNum;
    DebitTiliNum = DebitNum;

    if(DebitNum=="" && CreditNum != ""){
        qDebug()<<"Credit";
        debit = false;
        ValintaBool = false;
        sulku();
         }
     if(CreditNum=="" && DebitNum !=""){
       qDebug()<<"Debit if lauseen sisällä";
       ValintaBool = false;
       debit = true;
       sulku();
     } else {
       ValintaBool=true;
       creditptr->open();
      }
    }
 }



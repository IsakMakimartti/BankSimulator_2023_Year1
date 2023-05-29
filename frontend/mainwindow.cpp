#include "mainwindow.h"
#include "qobjectdefs.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Pankkiautomaatti");
    //Yhdistetään nappi clickHandleriin joka avaa rfidDLL:n
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(RFIDclickHandler()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::Kirjauduttu()
{
    //haetaan muuttujat KirjautumisDLL tiedostoista
    disconnect(kirjautumisptr,SIGNAL(sulkeutuu()),this,SLOT(Kirjauduttu()));
    Pinauth = kirjautumisptr->pinauth;
    Token = kirjautumisptr->token;
    TiliID = kirjautumisptr->TilinId;
    AsiakasID = kirjautumisptr->asiakasID;
    qDebug()<<"Asiakas ID:"+AsiakasID;
    CreditSaldo = kirjautumisptr->Creditsaldo;
    DebitSaldo = kirjautumisptr->Debitsaldo;
    CreditNum = kirjautumisptr->CreditTiliNum;
    DebitNum = kirjautumisptr->DebitTiliNum;
    Valinta = kirjautumisptr->ValintaBool;
    tiliptr = new Tili(this);  
    Debit = kirjautumisptr->debit;
    qDebug()<<Debit;
    qDebug()<<Valinta;
    qDebug()<<DebitNum;
    qDebug()<<CreditNum;
    if(DebitNum == "" && CreditNum != ""){
        Debit = false;
    }
    if(DebitNum != "" && CreditNum == ""){
        Debit = true;
    }

    //debug tietoja saaduista arvoista
    qDebug()<<"Pinauth: "<<Pinauth<<"Debit: "<<Debit;
    if(Pinauth == true){
        //tarkistus Booleani siitä onko tilillä monta Tiliä
     tiliptr->Valinta = Valinta;
     tiliptr->Tiliid = TiliID;
     tiliptr->token = Token;
     if(Debit == true){
         //asetetaan Tilinumero asiakkaan Uiihin
         tiliptr->Tilinum = DebitNum;
         tiliptr->Debit = Debit;
         tiliptr->tilihaku();
     }else{
         //asetetaan Tilinumero asiakkaan Uiihin
         tiliptr->Tilinum = CreditNum;
         tiliptr->Debit = Debit;
         tiliptr->tilihaku();
     }
     historiaptr = new Dialog(this);
     nostoptr = new NostoTalletus(this);
     talletusptr = new Talletus(this);
     tiliptr->open();
     connect(tiliptr, SIGNAL(creditDebit()),this,SLOT(creditDebitSlot()));
     connect(tiliptr, SIGNAL(kirjauduUlos()), this,SLOT(kirjauduUlosSlot()));
     connect(tiliptr, SIGNAL(talletus()), this,SLOT(talletusSlot()));
     connect(tiliptr, SIGNAL(nosto()), this,SLOT(nostoSlot()));
     connect(tiliptr, SIGNAL(historia()), this,SLOT(HistoriaSlot()));
     //päävalikkoon
    }
}

void MainWindow::RFIDclickHandler()
{
    //Avataan rfidDLL
    Pinauth = false;
    TiedonHaku = true;
    pRFID = new testiRFID(this);
    pRFID->open();
    //Vastaanotetaan kortin numero QString muodossa
    connect(pRFID,SIGNAL (sendCardNumber(QString)),
            this, SLOT(KortinNumeronPalautus(QString)));
}

void MainWindow::KortinNumeronPalautus(QString num)
{
    kirjautumisptr = new Kirjautumisikkuna(this);
    //Suljetaan rfidDLL ja tarkistetaan että DLL palautti kortin numeron.
    pRFID->close();
    //this->close();
    pRFID->deleteLater();
    pRFID = nullptr;
    num.resize(10);
    qDebug()<<"Kortin numero:"<<num;
    kirjautumisptr->DatabaseKey = num;
    kirjautumisptr->open();
    //KirjautumisIkkunan/Creditdebit ikkkunan sulkeutuessa tuleva signaali
    connect(kirjautumisptr,SIGNAL(sulkeutuu()),this,SLOT(Kirjauduttu()));
}

void MainWindow::creditDebitSlot()
{
    if(Debit == true){
        Debit = false;
    tiliptr->Tilinum = CreditNum;
     tiliptr->Debit = Debit;
    tiliptr->TiliNumSet();
    } else {
        Debit = true;
    tiliptr->Tilinum = DebitNum;
     tiliptr->Debit = Debit;
    tiliptr->TiliNumSet();
    }
}

void MainWindow::nostoSlot()
{
    qDebug()<<"NostoSLot";
    nostoptr = new NostoTalletus(this);
    nostoptr->databaseID = TiliID;
    nostoptr->AsiakasID = AsiakasID;
    nostoptr->token = Token;
    nostoptr->Debit = Debit;
    nostoptr->init();
    nostoptr->open();
    connect(nostoptr, SIGNAL(sendAmount(float,float)),
            this, SLOT(lukuVastaanotettuSlot(float,float)));
}

void MainWindow::talletusSlot()
{
    qDebug()<<"TalletusSlot";
    qDebug()<<TiliID;
    talletusptr = new Talletus(this);
    talletusptr->CreditSaldo = CreditSaldo;
    talletusptr->DebitSaldo = DebitSaldo;
    talletusptr->Debit = Debit;
    talletusptr->open();
    connect(talletusptr, SIGNAL(lahetys(float,float)),
            this, SLOT(lukuVastaanotettuSlot(float,float)));
}

void MainWindow::HistoriaSlot()
{
    qDebug()<<"HistoriaSLot"; 
    historiaptr->token = Token;
    historiaptr->Debit = Debit;
    historiaptr->TiliID = TiliID;
    historiaptr->getHistory();
    historiaptr->open();
}

void MainWindow::kirjauduUlosSlot()
{
    qDebug()<<"UlosKirjauduttu";
    qDebug()<<historiaptr;
    historiaptr->close();
    talletusptr->close();
    nostoptr->close();
    tiliptr->close();
    tiliptr->deleteLater();
    talletusptr->deleteLater();
    tiliptr->deleteLater();
    nostoptr->deleteLater();


}

void MainWindow::lukuVastaanotettuSlot(float saldoSent, float lukuSent)
{
    // Asetetaan saadut luvut muuttujiin saldoReveiced ja lukuReceived ja lasketaan ne yhteen muuttujaan newBalance
    float saldoReceived, lukuReceived, newBalance;
    tiliptr->tilihaku();
    if(Debit==true){
    saldoReceived = tiliptr->DebitSaldo.toFloat();
    }
    else{
        saldoReceived = tiliptr->CreditSaldo.toFloat();
    }
    qDebug()<<saldoSent;
    qDebug()<<lukuSent;
    lukuReceived = lukuSent;
    newBalance = saldoReceived + (lukuReceived);

    // Otetaan nykyinen pvm ja aika
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedTime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");

    QJsonObject jsonObj, jsonObj2;

    //Verrataan onko tili Debit vai Credit, ja päivitetään saldo. Sekä lähetetään tiedot nostoHistoriaan.
    if (Debit == true){
        jsonObj.insert("DebitSaldo",QString::number(newBalance));
        QString saldo_url="http://localhost:3000/debitSaldo/"+TiliID, history_url="http://localhost:3000/nosto";
        QNetworkRequest requestBalance((saldo_url)), requestHistory((history_url));
        requestBalance.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        requestHistory.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        //WEBTOKEN ALKU
        qDebug()<<Token;
        requestBalance.setRawHeader(QByteArray("Authorization"),(Token));
        requestHistory.setRawHeader(QByteArray("Authorization"),(Token));
        //WEBTOKEN LOPPU

        putManager = new QNetworkAccessManager(this);
        connect(putManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(updateBalanceSlot(QNetworkReply*)));

        replyBalance = putManager->put(requestBalance, QJsonDocument(jsonObj).toJson());

        jsonObj2.insert("DATETIME",formattedTime);
        jsonObj2.insert("MAARA",QString::number(lukuReceived));
        jsonObj2.insert("Debit",QString::number(1));
        jsonObj2.insert("idTili",TiliID);

        postManager = new QNetworkAccessManager(this);
        connect(postManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(postHistorySlot(QNetworkReply*)));

        replyHistory = postManager->post(requestHistory, QJsonDocument(jsonObj2).toJson());
    }
    else if (Debit == false)
    {
        jsonObj.insert("CreditSaldo",QString::number(newBalance));
        QString saldo_url="http://localhost:3000/creditSaldo/"+TiliID, history_url="http://localhost:3000/nosto";
        QNetworkRequest requestBalance((saldo_url)), requestHistory((history_url));
        requestBalance.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        requestHistory.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        //WEBTOKEN ALKU
        qDebug()<<Token;
        requestBalance.setRawHeader(QByteArray("Authorization"),(Token));
        requestHistory.setRawHeader(QByteArray("Authorization"),(Token));
        //WEBTOKEN LOPPU

        putManager = new QNetworkAccessManager(this);
        connect(putManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(updateBalanceSlot(QNetworkReply*)));

        replyBalance = putManager->put(requestBalance, QJsonDocument(jsonObj).toJson());

        jsonObj2.insert("DATETIME",formattedTime);
        jsonObj2.insert("MAARA",QString::number(lukuReceived));
        jsonObj2.insert("Debit",QString::number(0));
        jsonObj2.insert("idTili",TiliID);

        postManager = new QNetworkAccessManager(this);
        connect(postManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(postHistorySlot(QNetworkReply*)));

        replyHistory = postManager->post(requestHistory, QJsonDocument(jsonObj2).toJson());
    }
    else
    {
        qDebug()<<"Tiliä ei valittuna, saldon päivitys epäonnistui | LukuvastaanotettuSLOT";
    }
}
void MainWindow::updateBalanceSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    putManager->deleteLater();
    tiliptr->tilihaku();
}

void MainWindow::postHistorySlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    postManager->deleteLater();
}


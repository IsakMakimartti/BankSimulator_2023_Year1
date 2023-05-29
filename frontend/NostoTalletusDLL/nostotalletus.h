#ifndef NOSTOTALLETUS_H
#define NOSTOTALLETUS_H
//QT
#include <QDialog>
#include <QDebug>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QIntValidator>
//Own
#include "NostoTalletusDLL_global.h"

namespace Ui {
class NostoTalletus;
}

class NOSTOTALLETUSDLL_EXPORT NostoTalletus : public QDialog
{
    Q_OBJECT

public:
    explicit NostoTalletus(QWidget *parent = nullptr);
    ~NostoTalletus();
    static QString getBaseURLTili(); // Muokkaa myöhemmin
    static QString getBaseURLpvNostoRaja(); // Muokkaa myöhemmin
    QString databaseID,AsiakasID;
    void init();
    QByteArray token;
    bool Debit;

signals:
    void sendAmount(float, float);

private slots:
    void clickHandler10Euros();
    void clickHandler20Euros();
    void clickHandler50Euros();
    void clickHandler90Euros();
    void clickHandler140Euros();
    void clickHandler190Euros();
    void clickHandlerMuuSumma();
    void clickHandlerEnter();
    void clickHandlerPeruuta();

    void replyT(QNetworkReply*reply);
    void replyNRaja(QNetworkReply*reply);
private:
    //Objects and pointers
    Ui::NostoTalletus *ui;
    QString url;
    QNetworkAccessManager *getBalance, *getNostoRaja;
    QNetworkReply *replyTili, *replyNostoRaja;
    QByteArray response_data;
    QValidator * validator;

    float debitSaldo, creditSaldo, luottoRaja, nostoRaja;

    //Functions
    float checkNumber();
    void checkBalance();
};

#endif // NOSTOTALLETUS_H

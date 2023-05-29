#ifndef KIRJAUTUMISIKKUNA_H
#define KIRJAUTUMISIKKUNA_H
#include "creditdebit.h"
#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class Kirjautumisikkuna;
}

class Kirjautumisikkuna : public QDialog
{
    Q_OBJECT

public:
    explicit Kirjautumisikkuna(QWidget *parent = nullptr);
    ~Kirjautumisikkuna();
    bool pinauth = false;
    bool debit, ValintaBool;
    QByteArray token;
    const QByteArray &getToken() const;
    void setToken(const QByteArray &newToken);
    QString asiakasID, TilinId, Creditsaldo, Debitsaldo,DatabaseKey, CreditTiliNum, DebitTiliNum;
public slots:
    void pinkoodi();
private:
    void tilinhaku(QString a);
    int yritys = 3;
    QString URL = "http://localhost:3000";
    Ui::Kirjautumisikkuna *ui;
    QNetworkReply *reply;
    QByteArray response_data;
    CreditDebit * creditptr;
    QNetworkAccessManager * loginptr;

private slots:
 void pinkoodiGET(QNetworkReply *);
 void sulku();
 void on_Push_Kirjaudu_clicked();
 void Tilifinished(QNetworkReply *reply);
signals:
 void sulkeutuu();
};

#endif // KIRJAUTUMISIKKUNA_H

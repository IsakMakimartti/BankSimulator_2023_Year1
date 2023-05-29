#ifndef TILI_H
#define TILI_H
#include "TiliDLL_global.h"
#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QTimer>
namespace Ui {
class Tili;
}

class TILIDLL_EXPORT Tili : public QDialog
{
    Q_OBJECT

public:
    explicit Tili(QWidget *parent = nullptr);
    ~Tili();
    QString Tilinum,CreditSaldo,DebitSaldo,Tiliid;
    QByteArray token;
    bool Valinta,Debit;
    void TiliNumSet();
    void tilihaku();
private slots:
    void clickHandlerTilinValinta();
    void clickHandlerKirjauduUlos();
    void clickHandlerNosto();
    void clickHandlerHistoria();
    void clickHandlerTalletus();
    void Tilifinished(QNetworkReply *reply);
    void TimeOut();
private:
    Ui::Tili *ui;
    QNetworkReply *reply;
    QByteArray response_data;
    QNetworkAccessManager * tiliptr;
    QTimer aika;
    void timeStart();


signals:
    void nosto();
    void talletus();
    void historia();
    void kirjauduUlos();
    void creditDebit();
};

#endif // TILI_H

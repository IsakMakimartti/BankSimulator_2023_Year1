#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include "nostoTalletusHistoriaDLL_global.h"
#include <QStringList>

namespace Ui {
class Dialog;
}

class NOSTOTALLETUSHISTORIADLL_EXPORT Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void getHistory();
    QByteArray token;
    QString TiliID;
    bool Debit, Toisto;
    int Offset = 0;

public slots:
    void getHistorySlot(QNetworkReply*reply);

private slots:
    void edellinenHandler();
    void seuraavaHandler();
    void takaisinHandler();

private:
    Ui::Dialog *ui;
    QNetworkAccessManager * getHistoryManager;
    QNetworkReply *reply;
    int maaracounter;
    //QByteArray response_data;

};

#endif // DIALOG_H

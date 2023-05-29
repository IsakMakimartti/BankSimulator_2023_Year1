#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "kirjautumisikkuna.h"
#include "testirfid.h"
#include "tili.h"
#include "Dialog.h"
#include "TalletusDLL.h"
#include "nostotalletus.h"
#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Kirjautumisikkuna * kirjautumisptr;
    testiRFID *pRFID;
    Tili *tiliptr;
    NostoTalletus *nostoptr;
    Dialog *historiaptr;
    Talletus *talletusptr;

    //Onko kirjautuminen mennyt läpi ja mitä valittiin jos meni läpi
private:
    Ui::MainWindow *ui;
    bool Debit = NULL;
    bool Pinauth,Valinta,TiedonHaku = true;
    QByteArray Token;
    QString TiliID,AsiakasID,CreditSaldo,DebitSaldo,CreditNum,DebitNum;
    //QString TiliID,AsiakasID,CreditSaldo,DebitSaldo;
    QNetworkAccessManager *putManager; // nosto + talletus PUT - toiminnolle
    QNetworkAccessManager *postManager; // nosto + talletus POST - toiminnolle
    QNetworkReply * replyBalance, *replyHistory;
    QByteArray response_data;
public slots:
    void Kirjauduttu();
    void RFIDclickHandler();
    void KortinNumeronPalautus(QString num);
private slots:
    void creditDebitSlot();
    void nostoSlot();
    void talletusSlot();
    void HistoriaSlot();
    void kirjauduUlosSlot();
    void lukuVastaanotettuSlot(float, float); // nosto + talletus
    void updateBalanceSlot(QNetworkReply * reply); // nosto + talletus
    void postHistorySlot(QNetworkReply * reply); // nosto + talletus
};
#endif // MAINWINDOW_H

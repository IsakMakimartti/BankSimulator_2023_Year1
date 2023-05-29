#include "nostotalletus.h"
#include "ui_nostotalletus.h"

NostoTalletus::NostoTalletus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NostoTalletus)
{
    ui->setupUi(this);
    setWindowTitle("Nosto");
    ui->labelMaara->setText("Syötä nostettava määrä ja paina ENTER");

    validator = new QIntValidator(10, 999, this); // Asetetaan validator pointterille arvot välille 10-999
    ui->textNostoTalletus->setValidator(validator); /* Asetetaan tekstikentälle pointterin validator arvot,
    eli käyttäjä voi nyt syöttää vain kokonaislukuja väliltä 10-999*/

    //Yhdistetään buttonit niiden clickhandlereihin;
    connect(ui->button10Euros, SIGNAL(clicked(bool)),
            this, SLOT(clickHandler10Euros()));
    connect(ui->button20Euros, SIGNAL(clicked(bool)),
            this, SLOT(clickHandler20Euros()));
    connect(ui->button50Euros, SIGNAL(clicked(bool)),
            this, SLOT(clickHandler50Euros()));
    connect(ui->button90Euros, SIGNAL(clicked(bool)),
            this, SLOT(clickHandler90Euros()));
    connect(ui->button140Euros, SIGNAL(clicked(bool)),
            this, SLOT(clickHandler140Euros()));
    connect(ui->button190Euros, SIGNAL(clicked(bool)),
            this, SLOT(clickHandler190Euros()));
    connect(ui->buttonMuu, SIGNAL(clicked(bool)),
            this, SLOT(clickHandlerMuuSumma()));
    connect(ui->buttonEnter, SIGNAL(clicked(bool)),
            this, SLOT(clickHandlerEnter()));
    connect(ui->buttonPeruuta, SIGNAL(clicked(bool)),
            this, SLOT(clickHandlerPeruuta()));

}

NostoTalletus::~NostoTalletus()
{
    delete ui;
}

QString NostoTalletus::getBaseURLTili() // Poista myöhemmin ?
{
    return "http://localhost:3000/tili/";
}

QString NostoTalletus::getBaseURLpvNostoRaja() // Poista myöhemmin ?
{
    return "http://localhost:3000/asiakasTili/";
}

void NostoTalletus::init()
{
    //Haetaan asiakkaan tiedot
    QString tili_url=getBaseURLTili() + databaseID,
            asiakasTili_url = getBaseURLpvNostoRaja() + AsiakasID + "/" + databaseID;
    qDebug()<<tili_url;
    QNetworkRequest requestTili((tili_url)), requestAsiakasTili((asiakasTili_url));

    //WEBTOKEN ALKU
    qDebug()<<token;
    requestTili.setRawHeader(QByteArray("Authorization"),(token));
    requestAsiakasTili.setRawHeader(QByteArray("Authorization"),(token));
    //WEBTOKEN LOPPU

    getBalance = new QNetworkAccessManager(this);
    getNostoRaja = new QNetworkAccessManager(this);

    connect(getBalance, SIGNAL(finished (QNetworkReply*)), this, SLOT(replyT(QNetworkReply*)));
    replyTili = getBalance->get(requestTili);

    connect(getNostoRaja, SIGNAL(finished (QNetworkReply*)), this, SLOT(replyNRaja(QNetworkReply*)));
    replyNostoRaja = getNostoRaja->get(requestAsiakasTili);
}

void NostoTalletus::clickHandler10Euros()
{
    ui->textNostoTalletus->setText("10");
}

void NostoTalletus::clickHandler20Euros()
{
    ui->textNostoTalletus->setText("20");
}

void NostoTalletus::clickHandler50Euros()
{
    ui->textNostoTalletus->setText("50");
}

void NostoTalletus::clickHandler90Euros()
{
    ui->textNostoTalletus->setText("90");
}

void NostoTalletus::clickHandler140Euros()
{
    ui->textNostoTalletus->setText("140");
}

void NostoTalletus::clickHandler190Euros()
{
    ui->textNostoTalletus->setText("190");
}

void NostoTalletus::clickHandlerMuuSumma()
{
    ui->textNostoTalletus->setText("");
    ui->labelMaara->setText("Syötä nostettava määrä täyslukuna tekstikenttään ja paina ENTER\nMin. Määrä: 10€\nMax. Määrä: 400€");
}

void NostoTalletus::clickHandlerPeruuta()
{
    this->close();
}

float NostoTalletus::checkNumber()
{
    float luku = ui->textNostoTalletus->text().toFloat();
    return luku;
}

void NostoTalletus::clickHandlerEnter()
{

    /*Luetaan annettu teksti tekstikentästä nimeltä textNostoTalletus,
    muutetaan se float- tyyppiseksi ja talletetaan float- tyyppiseen muuttujaan nimeltä float*/
    float luku = checkNumber();

    // Muutetaan luku (float) int tyyppiseksi, jotta voidaan tarkistaa onko se 2:lla jaettava
    int tarkistus = luku;

    /*Tarkistetaan onko luku pienempi kuin 400, isompi kuin 10 ja onko luku 2:lla jaettava, koska automaatti antaa vain
    10,20,50€ seteleitä.
    Jos kaikki ehdot totta, haetaan saldo, luottoraja, päivänostoraja ja vertaillaan checkbalance()- funktion avulla */
    if((luku<=400.00) && (luku>= 10.00) && (tarkistus % 10 == 0))
    {
        checkBalance();
    }
    else if ((luku >= 10.00) && (tarkistus % 10 != 0))
    {
        ui->labelMaara->setText("Nosto epäonnistui\nHUOM. Anna Tasaluku\nMin. Määrä: 10€\nMax. Määrä: 400€");
    }
    else
    {
        ui->labelMaara->setText("Nosto epäonnistui\nMin. Määrä: 10€\nMax. Määrä: 400€");
    }
}

/* Funktio tarkistaa tietokannasta onko tilillä rahaa, onko päiväraja ylitetty tai luottoraja tullut vastaan. Jos kaikki ok,
lähettää mainwindowiin nostetun luvun */
void NostoTalletus::checkBalance()
{
    float luku = checkNumber();
    float creditTarkistus = creditSaldo + luottoRaja;

    if((debitSaldo>=luku) && (Debit == true))
    {
        if (nostoRaja>=luku)
        {
            qDebug()<<"NostoDLL | Tests passed. Sending deductable amount";
            emit sendAmount(debitSaldo,-luku);
            ui->labelMaara->setText("Nosto onnistui");
            this->close();
            //this->deleteLater();
        }
        else if (nostoRaja == 0)
        {
            qDebug()<<"NostoDLL | Tests passed. Sending deductable amount";
            emit sendAmount(debitSaldo,-luku);
            ui->labelMaara->setText("Nosto onnistui");
            this->close();
        }
        else
        {
            ui->labelMaara->setText("Nosto epäonnistui\nPäiväNostoraja ylitetty");
        }
    }
    else if((creditTarkistus>=luku) && (Debit == false))
    {
        if(nostoRaja>=luku)
        {
            qDebug()<<"NostoDLL | Tests passed. Sending deductable amount";
            emit sendAmount(creditSaldo,-luku);
            ui->labelMaara->setText("Nosto onnistui");
            this->close();
        }
        else if (nostoRaja == 0)
        {
            qDebug()<<"NostoDLL | Tests passed. Sending deductable amount";
            emit sendAmount(creditSaldo,-luku);
            ui->labelMaara->setText("Nosto onnistui");
            this->close();
        }
        else
        {
            ui->labelMaara->setText("Nosto epäonnistui\nPäiväNostoraja ylitetty");
        }
    }
    else
    {
          ui->labelMaara->setText("Nosto epäonnistui\nLuottoraja ylitetty");

    }
}

void NostoTalletus::replyT(QNetworkReply *replyTili)
{
    response_data=replyTili->readAll();
    //qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString dSaldo, cSaldo, lRaja;
    foreach (const QJsonValue &value, json_array) {
       QJsonObject json_obj = value.toObject();
       dSaldo+=QString::number(json_obj["DebitSaldo"].toDouble());
       cSaldo+=QString::number(json_obj["CreditSaldo"].toDouble());
       lRaja+=QString::number(json_obj["Luottoraja"].toDouble());
    }
    qDebug()<<"replyT funktiossa";

    qDebug()<<"Debit saldo : "+dSaldo;
    qDebug()<<"Credit Saldo : "+cSaldo;
    qDebug()<<"Luottoraja : "+lRaja;

    debitSaldo = dSaldo.toFloat();
    creditSaldo = cSaldo.toFloat();
    luottoRaja =lRaja.toFloat();

    replyTili->deleteLater();
    getBalance->deleteLater();
}

void NostoTalletus::replyNRaja(QNetworkReply *replyNostoRaja)
{
    response_data=replyNostoRaja->readAll();
    //qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString nRaja;
    foreach (const QJsonValue &value, json_array) {
       QJsonObject json_obj = value.toObject();
       nRaja+=QString::number(json_obj["PaivaNostoraja"].toDouble());
    }
    qDebug()<<"replyNRaja funktiossa";
    qDebug()<<"PaivaNostoraja : "+nRaja;
    nostoRaja = nRaja.toFloat();

    replyNostoRaja->deleteLater();
    getNostoRaja->deleteLater();
}

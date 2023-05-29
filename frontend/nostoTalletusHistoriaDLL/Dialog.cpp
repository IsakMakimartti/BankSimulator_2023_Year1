#include "Dialog.h"
#include "ui_Dialog.h"
#include "environment.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{

    //Tehdään connectit
    ui->setupUi(this);
    setWindowTitle("Nosto ja talletushistoria");
    connect(ui->edellinen,SIGNAL(clicked(bool)),this,SLOT(edellinenHandler()));
    connect(ui->seuraava,SIGNAL(clicked(bool)),this,SLOT(seuraavaHandler()));
    connect(ui->takaisin,SIGNAL(clicked(bool)),this,SLOT(takaisinHandler()));

    //Debug-arvoja mainwindowista tuoduille muuttujille
    qDebug()<<"TiliID:";
    qDebug()<<TiliID;
    qDebug()<<"token:";
    qDebug()<<token;
    qDebug()<<"history";
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::edellinenHandler()
{
    qDebug()<<"edellinen";

    //Katsotaan, onko offset-muuttuja erisuuri kuin nolla.
    //Jos offset on 0, edelliselle sivulle ei voi mennä
    //Jos offset on erisuuri kuin 0, offsettiä vähennetään viidellä ja edelliselle sivulle voi mennä
    if(Offset!=0){
    Offset = Offset-5;
    } else {
        qDebug()<<"Offset 0";
    }
    getHistory();

}

void Dialog::seuraavaHandler()
{
    qDebug()<<"seuraava";
    qDebug()<<maaracounter;
    maaracounter =maaracounter-1;
    //Katsotaan, onko tämän hetkisellä sivulla 5 arvoa, vai vähemmän.
    //Jos arvoja on vähemmän kuin 5, offsettiä ei kasvateta, eikä seuraavalle sivulle voi mennä
    //Jos arvoja on 5, offset kasvaa viidellä ja seuraavalle sivulle voi mennä
    if(maaracounter <5){
    qDebug()<<"Ei toisto";
    }
    else{
    Offset = Offset+5;
    }
    qDebug()<<Offset;
    getHistory();

}

void Dialog::takaisinHandler()
{
    qDebug()<<"takaisin";
    //UI suljetaan ja pointteri poistetaan
    this->close();
}

void Dialog::getHistory()
{

    //Muutetaan offset- ja debit-muuttujat QStringiksi get-requestia varten
    QString OffsetT = QString::number(Offset);
    QString DebitT = QString::number(Debit);

    //Debugit QStringiksi muutetuille arvoille
    qDebug()<<OffsetT;
    qDebug()<<DebitT;
    qDebug()<<"TiliID"+TiliID;

    //URLin asettaminen get-requestille
    QString site_url=Environment::getBaseUrl()+"/nostoH/"+DebitT+"/"+TiliID+"/"+OffsetT;

    qDebug()<<site_url;

    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(token));
    //WEBTOKEN LOPPU
    getHistoryManager = new QNetworkAccessManager(this);
    connect(getHistoryManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getHistorySlot(QNetworkReply*)));

    reply = getHistoryManager->get(request);
    qDebug()<<reply;
}
void Dialog::getHistorySlot(QNetworkReply*reply)
{    
    QByteArray response_data=reply->readAll();
         QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
         QJsonArray json_array = json_doc.array();
         QString vanhanostoID,idNostoHistoria,DATETIME,Debit,idTili,MAARA;
         foreach (const QJsonValue &value, json_array) {
           QJsonObject json_obj = value.toObject();
           idNostoHistoria+=QString::number(json_obj["idNostoHistoria"].toInt());
           DATETIME+=(json_obj["DATETIME"].toString())+",";
           MAARA+=QString::number(json_obj["MAARA"].toInt())+"€"+",";
           Debit+=QString::number(json_obj["Debit"].toInt());
           idTili+=QString::number(json_obj["idTili"].toInt());
         }

    //Arvot muutetaan QStringListeiksi ja eritellään toisistaan asettamalla niiden väliin pilkut ja splittaamalla
    QStringList MAARA1 = MAARA.split(",");
    int maara = MAARA1.count();
    maaracounter = MAARA1.count();
    QStringList DATETIME1 = DATETIME.split(",");

    //Tehdään muuttujat summien ja datetimen settaamiseen
    QString maaraSet;
    QString DATETIMEset;
    maara=maara-1;
    qDebug()<<idNostoHistoria;

    //Tyhjennetään labelit ennen sivun vaihtoa, etteivät vanhat arvot jää näkyviin sivun vaihtuessa
    if(idNostoHistoria != vanhanostoID){
        for(int x=0;x<5;x++){
                    switch (x){
                    case 0:
                        ui->aika1->setText("");
                        ui->maara1->setText("");
                        break;
                    case 1:
                        ui->aika2->setText("");
                        ui->maara2->setText("");
                        break;
                    case 2:
                        ui->aika3->setText("");
                        ui->maara3->setText("");
                        break;
                    case 3:
                        ui->aika4->setText("");
                        ui->maara4->setText("");
                        break;
                    case 4:
                        ui->aika5->setText("");
                        ui->maara5->setText("");
                        break;
                  }
        }
        //Asetetaan labeleihin nostojen/talletusten määrät
        for(int x=0;x<maara;x++){
            switch (x){
            case 0:
                maaraSet = MAARA1[x];
                ui->maara1->setText(maaraSet);
                break;
            case 1:
                maaraSet = MAARA1[x];
                ui->maara2->setText(maaraSet);
                break;
            case 2:
                maaraSet = MAARA1[x];
                ui->maara3->setText(maaraSet);
                break;
            case 3:
                maaraSet = MAARA1[x];
                ui->maara4->setText(maaraSet);
                break;
            case 4:
                maaraSet = MAARA1[x];
                ui->maara5->setText(maaraSet);
                break;
            }

            //Asetetaan labeleihin nostojen/talletusten tapahtuma-ajat
            for(int x=0;x<maara;x++){
                switch (x){
                case 0:
                    DATETIMEset = DATETIME1[x].replace("T"," ").replace("Z"," ").remove(19,22);
                    ui->aika1->setText(DATETIMEset);
                    break;
                case 1:
                    DATETIMEset = DATETIME1[x].replace("T"," ").replace("Z"," ").remove(19,22);
                    ui->aika2->setText(DATETIMEset);
                    break;
                case 2:
                    DATETIMEset = DATETIME1[x].replace("T"," ").replace("Z"," ").remove(19,22);
                    ui->aika3->setText(DATETIMEset);
                    break;
                case 3:
                    DATETIMEset = DATETIME1[x].replace("T"," ").replace("Z"," ").remove(19,22);
                    ui->aika4->setText(DATETIMEset);
                    break;
                case 4:
                    DATETIMEset = DATETIME1[x].replace("T"," ").replace("Z"," ").remove(19,22);
                    ui->aika5->setText(DATETIMEset);
                    break;
                }

        }
     Toisto = false;
    }
    } else {
     qDebug()<<"toistoa";
     Toisto = true;
    }
    reply->deleteLater();
    getHistoryManager->deleteLater();
}

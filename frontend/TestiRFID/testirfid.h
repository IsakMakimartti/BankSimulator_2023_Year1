#ifndef TESTIRFID_H
#define TESTIRFID_H

#include <QDialog>
#include <QDialog>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QTimer>

namespace Ui {
class testiRFID;
}

class testiRFID : public QDialog
{
    Q_OBJECT

public:
    explicit testiRFID(QWidget *parent = nullptr);
    ~testiRFID();
private slots:
    void Read_Data();
    void TimeOut();

signals:
    void sendCardNumber(QString);
private:
    Ui::testiRFID *ui;
    QSerialPort* COMPORT;
    QString Data_From_SerialPort;
    QTimer aika;
};

#endif // TESTIRFID_H

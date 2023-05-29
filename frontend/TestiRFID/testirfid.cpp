#include "testirfid.h"
#include "ui_testirfid.h"
#include <QSerialPort>
#include <QSerialPortInfo>

testiRFID::testiRFID(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::testiRFID)
{
    ui->setupUi(this);

    setWindowTitle("RFID-kortinlukija");

    //Avataan SerialPortti
    COMPORT = new QSerialPort();

    COMPORT->setPortName("COM5");

    COMPORT->setBaudRate(QSerialPort::Baud9600);
    COMPORT->setParity(QSerialPort::Parity::NoParity);
    COMPORT->setDataBits(QSerialPort::DataBits::Data8);
    COMPORT->setStopBits(QSerialPort::StopBits::OneStop);
    COMPORT->setFlowControl(QSerialPort::FlowControl::NoFlowControl);
    COMPORT->open(QIODevice::ReadWrite);

    //Testataan onko SerialPortti auki
    if (COMPORT->isOpen())
    {
        qDebug()<<"SerialPort is Connected";
    }

    else
    {
        qDebug()<<"SerialPort is NOT Connected";
    }

    //Aloitetaan timeout ajastin
    connect(&aika,SIGNAL(timeout()),
            this,SLOT(TimeOut()));
    aika.start(10000);

    //Siirrytään Read_Data funktioon
    connect(COMPORT, SIGNAL(readyRead()),this,SLOT(Read_Data()));
}

testiRFID::~testiRFID()
{
    delete ui;
}

void testiRFID::Read_Data()
{
    qDebug()<<"Read_Data";
    if (COMPORT->isOpen())
    {
        while (COMPORT->bytesAvailable())
        {
            //Luetaan SerialPortilta tuleva data ja poistettaan siitä turhat osuudet
            Data_From_SerialPort +=COMPORT->readAll();
            Data_From_SerialPort.remove(0, 3);
            Data_From_SerialPort.remove(10, 14);
            Data_From_SerialPort.resize(10);
            qDebug()<<"Data From SerialPort :"<<Data_From_SerialPort;
            emit sendCardNumber(Data_From_SerialPort);
            Data_From_SerialPort = "";
            this->close();
            COMPORT->deleteLater();
        }
    }

}

void testiRFID::TimeOut()
{
    qDebug()<<"RFID TimeOut";
    this->close();
}



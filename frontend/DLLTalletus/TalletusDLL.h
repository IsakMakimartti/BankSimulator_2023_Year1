#ifndef TALLETUSDLL_H
#define TALLETUSDLL_H

#include "TalletusDLL_global.h"
#include <QDialog>
#include <QDebug>
#include <QIntValidator>

namespace Ui {
class Talletus;
}

class TALLETUSDLL_EXPORT Talletus : public QDialog
{
    Q_OBJECT

public:
    explicit Talletus(QWidget *parent = nullptr);
    ~Talletus();
    float lahetettavaLuku;
    QString CreditSaldo, DebitSaldo;
    bool Debit;

private slots:
    void clickHandlerEnter();
    void clickHandlerEdellinen();

private:
    Ui::Talletus *ui;
    QValidator * validator;

signals:
    void lahetys(float, float);
    void update();
};

#endif // TALLETUSDLL_H

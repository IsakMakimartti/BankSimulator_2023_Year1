#ifndef CREDITDEBIT_H
#define CREDITDEBIT_H

#include <QDialog>

namespace Ui {
class CreditDebit;
}

class CreditDebit : public QDialog
{
    Q_OBJECT

public:
    explicit CreditDebit(QWidget *parent = nullptr);
    ~CreditDebit();
    bool Debit = NULL;
    bool CreditDebitIkkuna;
private:
    Ui::CreditDebit *ui;
private slots:
    void valinta();
signals:
    void sulkuu();

};

#endif // CREDITDEBIT_H

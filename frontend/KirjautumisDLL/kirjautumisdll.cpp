#include "kirjautumisdll.h"
#include <QDebug>
KirjautumisDLL::KirjautumisDLL()
{
    //tehdään uin pointeri
    ikkunaptr = new Kirjautumisikkuna;
    qDebug()<<"KirjautumisDLL";
    //avataan ui
    //ikkunaptr->open();
}

void KirjautumisDLL::open()
{
    qDebug()<<"Open";
    ikkunaptr->open();
}

#ifndef KIRJAUTUMISDLL_H
#define KIRJAUTUMISDLL_H

#include "KirjautumisDLL_global.h"
#include "kirjautumisikkuna.h"
class KIRJAUTUMISDLL_EXPORT KirjautumisDLL
{
public:
    KirjautumisDLL();
    Kirjautumisikkuna * ikkunaptr;
    void open();
};

#endif // KIRJAUTUMISDLL_H

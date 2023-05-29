#ifndef NOSTOTALLETUSDLL_GLOBAL_H
#define NOSTOTALLETUSDLL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NOSTOTALLETUSDLL_LIBRARY)
#  define NOSTOTALLETUSDLL_EXPORT Q_DECL_EXPORT
#else
#  define NOSTOTALLETUSDLL_EXPORT Q_DECL_IMPORT
#endif

#endif // NOSTOTALLETUSDLL_GLOBAL_H

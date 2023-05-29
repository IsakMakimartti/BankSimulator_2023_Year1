#ifndef TILIDLL_GLOBAL_H
#define TILIDLL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TILIDLL_LIBRARY)
#  define TILIDLL_EXPORT Q_DECL_EXPORT
#else
#  define TILIDLL_EXPORT Q_DECL_IMPORT
#endif

#endif // TILIDLL_GLOBAL_H

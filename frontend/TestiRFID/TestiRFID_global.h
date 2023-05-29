
#ifndef TESTIRFID_GLOBAL_H
#define TESTIRFID_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TESTIRFID_LIBRARY)
#  define TESTIRFID_EXPORT Q_DECL_EXPORT
#else
#  define TESTIRFID_EXPORT Q_DECL_IMPORT
#endif

#endif // TESTIRFID_GLOBAL_H

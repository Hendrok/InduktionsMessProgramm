#ifndef INDUCORE_GLOBAL_H
#define INDUCORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(INDUCORE_LIBRARY)
#  define INDUCORE_EXPORT Q_DECL_EXPORT
#else
#  define INDUCORE_EXPORT Q_DECL_IMPORT
#endif

#endif // INDUCORE_GLOBAL_H

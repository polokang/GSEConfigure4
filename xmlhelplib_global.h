#ifndef XMLHELPLIB_GLOBAL_H
#define XMLHELPLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(XMLHELPLIB_LIBRARY)
#  define XMLHELPLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define XMLHELPLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // XMLHELPLIB_GLOBAL_H

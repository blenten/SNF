#ifndef SNF_LIB_GLOBAL_H
#define SNF_LIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SNF_LIB_LIBRARY)
#  define SNF_LIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SNF_LIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SNF_LIB_GLOBAL_H
